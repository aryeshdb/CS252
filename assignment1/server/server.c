/* credit @Daniel Scocco */

/****************** SERVER CODE ****************/

#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAXSIZE 10000

char sendbuffer[MAXSIZE];
char recvbuffer[MAXSIZE];
int requiredImages[4];

void cleanbuffer(char buf[]){
	int i=0;
	for(i=0;i<MAXSIZE;i++)buf[i]='0';
}

void parseQuery(){
	requiredImages[0]=0;  //cars
	requiredImages[1]=0;  //cats
	requiredImages[2]=0;  //dogs
	requiredImages[3]=0;  //trucks
	int len= strlen(recvbuffer);
	int i=0;
	while(recvbuffer[i]!='\0'){
		int value;
		if(recvbuffer[i]=='1') {value=1;i+=2;}
		else if(recvbuffer[i]=='2') {value=2;i+=2;}
		else if(recvbuffer[i]=='3') {value=3;i+=2;}
		else if(recvbuffer[i]=='4') {value=4;i+=2;}
		else {i+=4;continue;}
		if(recvbuffer[i]=='c' && recvbuffer[i+1]=='a' && recvbuffer[i+2]=='r'){
			i+=4;
			requiredImages[0]=value;
		}
		else if(recvbuffer[i]=='c' && recvbuffer[i+1]=='a' && recvbuffer[i+2]=='t'){
			i+=4;
			requiredImages[1]=value;
		}
		else if(recvbuffer[i]=='d' && recvbuffer[i+1]=='o' && recvbuffer[i+2]=='g'){
			i+=4;
			requiredImages[2]=value;
		}
		else {
			i+=6;
			requiredImages[3]=value;
		}

		if(recvbuffer[i]==' ')i++;
	}
	return;
}

void sendimage(int newSocket){
	int c;
	int i=0;
	FILE *file;
	printf("%s\n",recvbuffer);
	file = fopen(recvbuffer, "rb");
	if(file==NULL)printf("no file found\n");
	if (file!=NULL) {
	    while ((c = getc(file)) != EOF){
	        sendbuffer[i]=c;
	    	i++;
	    	if(i==(MAXSIZE)){
				send(newSocket,sendbuffer,MAXSIZE,0);
				cleanbuffer(sendbuffer);
				i=0;	    
	    	}
	    }	
	    fclose(file);
	    if(i!=0){
			send(newSocket,sendbuffer,MAXSIZE,0);
	    }
	    
		cleanbuffer(sendbuffer);
		sendbuffer[0]='d';sendbuffer[1]='o';sendbuffer[2]='n';sendbuffer[3]='e';
		send(newSocket,sendbuffer,4,0);
		printf("done sending image\n");
	}
	return;
}

int main(){
	int welcomeSocket, newSocket;
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;
	welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5432);
	/* Set IP address to localhost */
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
	bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
	if(listen(welcomeSocket,5)==0)
	  printf("I'm listening\n");
	else
	  printf("Error\n");


	while(1){
		
		addr_size = sizeof serverStorage;
		newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);


		recv(newSocket, recvbuffer, MAXSIZE, 0);
		parseQuery();
		int j;
		for(j=0;j<4;j++){
			if(requiredImages[j]==0)continue;
			int k;
			for(k=1;k<=requiredImages[j];k++){
				recvbuffer[0]='i';recvbuffer[1]='m';recvbuffer[2]='a';recvbuffer[3]='g';recvbuffer[4]='e';recvbuffer[5]='s';recvbuffer[6]='/';
				if(k==1)recvbuffer[12]='1';
				else if(k==2)recvbuffer[12]='2';
				else if(k==3)recvbuffer[12]='3';
				else if(k==4)recvbuffer[12]='4';
				if(j==0){
					recvbuffer[7]='c';recvbuffer[8]='a';recvbuffer[9]='r';recvbuffer[10]='s';recvbuffer[11]='/'; recvbuffer[13]='.';recvbuffer[14]='j';recvbuffer[15]='p';recvbuffer[16]='g';
				}
				else if(j==1){
					recvbuffer[7]='c';recvbuffer[8]='a';recvbuffer[9]='t';recvbuffer[10]='s';recvbuffer[11]='/';recvbuffer[13]='.';recvbuffer[14]='j';recvbuffer[15]='p';recvbuffer[16]='g';	
				}
				else if(j==2){
					recvbuffer[7]='d';recvbuffer[8]='o';recvbuffer[9]='g';recvbuffer[10]='s';recvbuffer[11]='/';recvbuffer[13]='.';recvbuffer[14]='j';recvbuffer[15]='p';recvbuffer[16]='g';	
				}
				else if(j==3){
					recvbuffer[7]='t';recvbuffer[8]='r';recvbuffer[9]='u';recvbuffer[10]='s';recvbuffer[11]='/';recvbuffer[13]='.';recvbuffer[14]='j';recvbuffer[15]='p';recvbuffer[16]='g';	
				}
				recvbuffer[17]='\0';
				sendimage(newSocket);
				sleep(5);
			}
				
		}
		
	}
  return 0;
}
