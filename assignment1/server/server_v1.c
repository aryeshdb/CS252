/* credit @Daniel Scocco */

/****************** SERVER CODE ****************/

#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define MAXSIZE 10000

char sendbuffer[MAXSIZE];
char recvbuffer[MAXSIZE];
int requiredImages[4];

void cleanbuffer(char buf[]){
	int i=0;
	for(i=0;i<MAXSIZE;i++)buf[i]='0';
}
void sendimage(int newSocket){
	int c;
	int i=0;
	FILE *file;
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
		sendimage(newSocket);
	}
  return 0;
}
