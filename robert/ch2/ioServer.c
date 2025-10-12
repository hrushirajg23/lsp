/*
The select system call is used for I/O multiplexing, 
allowing a program to monitor multiple file descriptors to 
see if any of them are ready for I/O operations 
(read, write, or exceptional conditions). This is particularly
useful in scenarios where a program needs to handle multiple 
input/output sources concurrently without using
multi-threading.
*/
/*

Practical Use Case: A Simple Chat Server
Let's consider a simple chat server that needs to handle
multiple client connections simultaneously. The server
should be able to:

Accept new client connections.
Receive messages from connected clients.
Broadcast received messages to all connected clients
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/select.h>

#define PORT 12345
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024


int main(){
     int server_fd,client_fd,max_sd,activity,new_socket;
     int client_socket[MAX_CLIENTS];
     struct sockaddr_in address;
     fd_set readfs;
     char Buffer[BUFFER_SIZE];

     //initialize all clients to zero
     for(int i=0;i<MAX_CLIENTS;i++){
          client_socket[i]=0;
     }
     /*
          AF_INET -> IPv4
          SOCK_STREAM -> TCP socket

     */
     if((server_fd=socket(AF_INET,SOCK_STREAM,0))==-1){
          perror("socket failed");
          exit(EXIT_FAILURE);
     }     

     address.sin_family=AF_INET; //ipv4
     address.sin_addr.s_addr=INADDR_ANY;
     address.sin_port=htons(PORT);

     //Binding socket to address
     if(bind(server_fd,(struct sockaddr*)&address,sizeof(address))<0){
          perror("bind failed");
          close(server_fd);
          exit(EXIT_FAILURE);
     }     


     if(listen(server_fd,3)<0){
          perror("listen failed");
          close(server_fd);
          exit(EXIT_FAILURE);
     }

     printf("Listening to port %d\n",PORT);

     while(1){
          FD_ZERO(&readfs);
          FD_SET(server_fd,&readfs);
          max_sd=server_fd;
          for(int i=0;i<MAX_CLIENTS;i++){
               client_fd=client_socket[i];

               if(client_fd >0){
                    FD_SET(client_fd,&readfs);
               }
               if(client_fd > max_sd){
                    max_sd =client_fd;
               }
          }

          //on success the select system call returns the number
          //of file desc's ready for I/O among all three sets

          activity=select(max_sd+1,&readfs,NULL,NULL,NULL);
          if(FD_ISSET(server_fd,&readfs)){
               socklen_t addrlen=sizeof(address);
               if((new_socket=accept(server_fd,(struct sockaddr*)&address,&addrlen))<0){
                    perror("accept failed");
                    exit(EXIT_FAILURE);
               }
               printf("New connection, socket fd is %d, ip is : %s, port : %d\n",new_socket,inet_ntoa(address.sin_addr),ntohs(address.sin_port));
               for (int i = 0; i < MAX_CLIENTS; i++) {
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n", i);
                    break;
               }

               
            }
                      //check other sockets for activity
          for(int i=0;i<MAX_CLIENTS;i++){
               client_fd=client_socket[i];
               if(FD_ISSET(client_fd,&readfs)){
                    int valread=read(client_fd,Buffer,BUFFER_SIZE);
                    if(valread==0){
                         getpeername(client_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen);
                         printf("Host disconnected , ip %s , port %d\n",inet_ntoa(address.sin_addr),ntohs(address.sin_port));
                         close(client_fd);
                         client_socket[i]=0;
                    }
                    else{
                         //broadcast the message to all other clients
                         Buffer[valread]='\0';
                         for(int j=0;j<MAX_CLIENTS;j++){
                              if(client_socket[j]!=0 && client_socket[j]!=client_fd){
                                   send(client_socket[j],Buffer,strlen(Buffer),0);
                              }
                         }
                    }
               }
          }
          }


     }
     return 0;
}
