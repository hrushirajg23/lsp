#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#define BUF 1024
int main(){
     
     int fd=0,fd2=0;
     if((fd=open("kern.txt",O_RDONLY))==-1){
          perror("open");
          exit(EXIT_FAILURE);
     }
     char Buffer[BUF];
     int iRet=0;
     if((fd2=open("pokemon.txt",O_WRONLY |O_NONBLOCK | O_TRUNC | O_APPEND | O_CREAT,0644 ))==-1){
          perror("open");
          exit(EXIT_FAILURE);
     }
     
     while((iRet=read(fd,Buffer,BUF))!=EOF){
          if(iRet==-1){
               if(errno==EINTR){
                    continue;
               }
               perror("read");
               break;
          }
               write(fd2,Buffer,iRet);
          
     }
     return 0;
}