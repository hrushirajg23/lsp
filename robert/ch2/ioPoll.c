#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<poll.h>
#include<fcntl.h>
#include<errno.h>
#define TIMEOUT 5

#define BUFSIZE 512
char Buffer[BUFSIZE];
int main(){
     struct pollfd fds[2];
     int ret;

     /*
          WATCH STDIN for input
     */
     
     if((fds[0].fd=open("polar.txt",O_RDWR | O_NONBLOCK))==-1){
          
               perror("error reading");
               exit(EXIT_FAILURE);
          
     }
   //  fds[0].fd=STDIN_FILENO;
     fds[0].events=POLLIN;

     /*
          watch STDIN for output
     */

    fds[1].fd=STDOUT_FILENO;
    fds[1].events=POLLOUT;

     /*
          On success the poll() call returns the number 
          of file descriptors whose structures have non-zero 
          revent fields
     */
    int r=0,w=0;
    ret=poll(fds,2,TIMEOUT*1000);
    if(ret==-1){
          perror("poll");
          return -1;
    }
    if(!ret){
     printf("%d seconds elapsed\n",TIMEOUT);
     return 0;
    }

    if(fds[0].revents & POLLIN){
     printf("file is readable\n");
     start:
          r=read(fds[0].fd,Buffer,BUFSIZ);
          if(r==-1){
               if(errno==EINTR){
                    goto start;
               }
               if(errno == EAGAIN){
                    /*resubmit later*/
               }
               else{
                    perror("error reading");
                    exit(EXIT_FAILURE);
               }
          }
    }

    if(fds[1].revents & POLLOUT){
     printf("writing file is ready\n");
     write(fds[1].fd,Buffer,r);

    }


     return 0;
}