#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>

char Buffer[512];
int main(){
     int fd;
     if((fd=open("default.txt",O_RDWR))==-1){
          perror("open");
          exit(EXIT_FAILURE);
     }
     /*
          Now my file size is 6 bytes and I place the offset
          160 bytes ahead of 6 bytes. Those 160 bytes will 
          be padded with zeros. This padding is called a hole, 
          its binary in nature (NULL). They don't occupy any space on disk
          Files with holes are called SPARSE FILES 
     
     */
     int pos=lseek(fd,(off_t)160,SEEK_END);
     if(pos==-1){
          perror("lseek");
          exit(EXIT_FAILURE);
     }
     char* str="hell noooooooo";
     start:
     int iRet=write(fd,str,strlen(str));
     if(iRet==-1){
          if(errno==EINTR){
               goto start;
          }
          perror("write");
          exit(EXIT_FAILURE);
     }
     int total=0;
     while((iRet=read(fd,Buffer,512))!=EOF){
          total+=iRet;
          write(STDOUT_FILENO,Buffer,iRet);
     }
     printf("\n read %d bytes \n",total);

     return 0;
}