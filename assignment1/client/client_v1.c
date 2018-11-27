
/* credit @Daniel Scocco */

/****************** CLIENT CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#define MAXSIZE 10000

char sendbuffer[MAXSIZE];
char recvbuffer[MAXSIZE];

void cleanbuffer(char buf[]){
  int i=0;
  for(i=0;i<MAXSIZE;i++)buf[i]='0';
}

void sendQueryAndReceiveImage(int clientSocket){
  int len= strlen(sendbuffer);
  sendbuffer[len]='\0';
  send(clientSocket,sendbuffer,len+1,0);
  

  recv(clientSocket, recvbuffer, MAXSIZE, 0);
  FILE *fptr;
  fptr = fopen("image.jpg", "wb");
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
  fptr = fopen("image.jpg", "ab");
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

  while(1){
    scanf("%s",sendbuffer);
    sendQueryAndReceiveImage(clientSocket);
  }
    
  return 0;
}
