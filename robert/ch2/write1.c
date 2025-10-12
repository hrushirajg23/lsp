#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
ssize_t ret,nr;

int len=1024;

int main(){
     int fd=open("kern.txt",O_WRONLY);
     if(fd==-1){
          perror("open");
          exit(EXIT_FAILURE);
     }
     char *buf="major minor device drivers to be written ";
     while(len!=0 && (ret=write(fd,buf,len))!=0){
          if(ret==-1){
               if(errno==EINTR)
                    continue;
               perror("write");
               break;
          }
          len-=ret;
          buf+=ret;
     }

     return 0;
}