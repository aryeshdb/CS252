
/* credit @Daniel Scocco */

/****************** CLIENT CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXSIZE 10000

char sendbuffer[MAXSIZE];
char recvbuffer[MAXSIZE];
int requiredImages[4];

void cleanbuffer(char buf[]){
  int i=0;
  for(i=0;i<MAXSIZE;i++)buf[i]='0';
}

void sendQuery(int clientSocket ){
  int c,i;
  i=0;
  c=getchar();
  // printf("%c\n",c);
  while(c!='\n'){
    sendbuffer[i]=c;
    i++;
    c=getchar();
  }
  int len= strlen(sendbuffer);
  sendbuffer[len]='\0';
  send(clientSocket,sendbuffer,len+1,0);
}

void parseQuery(){
  requiredImages[0]=0;  //cars
  requiredImages[1]=0;  //cats
  requiredImages[2]=0;  //dogs
  requiredImages[3]=0;  //trucks
  int len= strlen(sendbuffer);
  int i=0;
  while(sendbuffer[i]!='\0'){
    int value;
    if(sendbuffer[i]=='1') {value=1;i+=2;}
    else if(sendbuffer[i]=='2') {value=2;i+=2;}
    else if(sendbuffer[i]=='3') {value=3;i+=2;}
    else if(sendbuffer[i]=='4') {value=4;i+=2;}
    else {i+=4;continue;}
    if(sendbuffer[i]=='c' && sendbuffer[i+1]=='a' && sendbuffer[i+2]=='r'){
      i+=4;
      requiredImages[0]=value;
    }
    else if(sendbuffer[i]=='c' && sendbuffer[i+1]=='a' && sendbuffer[i+2]=='t'){
      i+=4;
      requiredImages[1]=value;
    }
    else if(sendbuffer[i]=='d' && sendbuffer[i+1]=='o' && sendbuffer[i+2]=='g'){
      i+=4;
      requiredImages[2]=value;
    }
    else {
      i+=6;
      requiredImages[3]=value;
    }

    if(sendbuffer[i]==' ')i++;
  }
  return;
}

void ReceiveImage(int clientSocket,int imagenum){
  int len;
  recv(clientSocket, recvbuffer, MAXSIZE, 0);
  char imageloc[1024];
  imageloc[0]='i';imageloc[1]='m';imageloc[2]='a';imageloc[3]='g';imageloc[4]='e';imageloc[5]='s';imageloc[6]='/';imageloc[7]=(char)(imagenum+48);imageloc[8]='.';imageloc[9]='j';imageloc[10]='p';imageloc[11]='g';imageloc[12]='\0';
  FILE *fptr;
  fptr = fopen(imageloc, "wb");
  if(fptr == NULL)
  {
     printf("Error!");
     exit(1);
  }
  int counter=0;
  for(counter=0;counter<(MAXSIZE);counter++){
    fprintf(fptr,"%c", recvbuffer[counter]);
  }

  fclose(fptr);
  fptr = fopen(imageloc, "ab");
  while(1){
    cleanbuffer(recvbuffer);
    recv(clientSocket, recvbuffer, MAXSIZE, 0);
    if( recvbuffer[0]=='d' && recvbuffer[1]=='o' && recvbuffer[2]=='n' && recvbuffer[3]=='e'){
      printf("done receiving image\n");
      break;
    } 
    else{
      if(fptr == NULL)
      {
         printf("Error!");
         exit(1);
      }
      for(counter=0;counter<(MAXSIZE);counter++){
        fprintf(fptr,"%c", recvbuffer[counter]);  
      }
      
      
    } 
  }
  fclose(fptr);
  return;
}

int main(){
  int clientSocket;
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(5432);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

  int flag=1;
  while(1){
    sendQuery(clientSocket);
    parseQuery();
    int j;int imagenum=1;
    for(j=0;j<4;j++){
      if(requiredImages[j]==0)continue;
      int k;
      for(k=1;k<=requiredImages[j];k++){
        ReceiveImage(clientSocket,imagenum);
        sleep(5);
        imagenum++;
      }
      flag=1;
    }
    if(flag==1)break;
  }
  
  system("./render.sh"); 
  return 0;
}
