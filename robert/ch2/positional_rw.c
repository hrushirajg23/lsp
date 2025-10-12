#define _XOPEN_SOURCE 500

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>

/*

     Positional read and write are mixture of lseek with read
     and write. They receive the file's position from which to read
     or write. 
     UPON COMPLETION THEY do NOT update the file POSITION

*/
#define SIZE 512
char Buffer[SIZE];

int fd;

int main(){
     if((fd=open("default.txt",O_RDWR))==-1){
          perror("open");
          exit(EXIT_FAILURE);
     }
     
     ssize_t iRet=pread(fd,Buffer,SIZE,0);
     if((write(STDOUT_FILENO,Buffer,iRet))==-1){
          perror("write");
          exit(EXIT_FAILURE);
     }
     iRet=lseek(fd,0,SEEK_CUR);
     printf("current offset %ld\n",iRet);
     /*
     
     
     */

}