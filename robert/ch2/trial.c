#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/stat.h>
#include<string.h>

int main(){
     int fd=0,offset,iRet=0;

     char Buff[]="hey everyone , linux system programming";
     char buff[sizeof(Buff)];

     fd=open("default.txt",O_RDWR);
     if(fd==-1){
          perror("Couldn't open file");
          exit(EXIT_FAILURE);
     }
     iRet=write(fd,Buff,sizeof(Buff));
     if(iRet==-1 || iRet!=sizeof(Buff)){
          perror("Couldn't write contents");
          return 1;
     }
     lseek(fd,0,SEEK_SET);


     iRet=read(fd,buff,sizeof(Buff));
     if(iRet==-1){
          perror("Couldn' read file");
          return 1;
     }
     printf("read file is %s\n",buff);
     return 0;
}