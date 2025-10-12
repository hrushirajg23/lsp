#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


#define PORT 12345
#define BUFFER_SIZE 1024


int main(){
     int sock=0;
     struct sockaddr_in serv_addr;
     char Buffer[BUFFER_SIZE]={0};
     char message[BUFFER_SIZE];


     if((sock=socket(AF_INET,SOCK_STREAM,0))<0){
          puts("socket creation error\n");
          exit(EXIT_FAILURE);
     }

     serv_addr.sin_family=AF_INET;
     serv_addr.sin_port=htons(PORT);

     if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)<=0){
          puts("invalid address , not supported\n");
          return -1;
     }

     if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
          puts("Connection failed\n");
          return -1;
     }

     while(1){
          printf("Enter message\n");
          fgets(message,BUFFER_SIZE,stdin);
          send(sock,message,strlen(message),0);
          int val_read=read(sock,Buffer,BUFFER_SIZE);
          Buffer[val_read]='\0';
          printf("Server : %s\n",Buffer);
     }
     return 0;
}