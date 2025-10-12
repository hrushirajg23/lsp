#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
int main(){
     char Buffer[40];
     int fd=open("kern.txt",O_RDWR );
     if(fd==-1){
          perror("open");
          exit(EXIT_FAILURE);
     }
     int iRet=0;
     off_t pos=lseek(fd,0,SEEK_CUR);
     printf("current postion is %ld\n",pos);
     if((iRet=read(fd,Buffer,40))==-1){
          perror("read");
          printf("read %d bytes\n",iRet);
          write(STDOUT_FILENO,Buffer,40);
          exit(EXIT_FAILURE);
     }

     return 0;
}