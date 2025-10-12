#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/select.h>
#include<sys/time.h>
#include<unistd.h>

int main(){

     fd_set readfs;
     struct timeval tv;
     int retval;

     FD_ZERO(&readfs);
     FD_SET(STDIN_FILENO,&readfs);


     tv.tv_sec=5;
     tv.tv_usec=0;


     retval=select(1,&readfs,NULL,NULL,&tv);
     int iRet=read();
     if(retval==-1){
          perror("select()");
     }
     else if(retval){
          printf("Data is avaliable now\n");
     }
     else{
          printf("No data within 5 seconds\n");
     }

     return 0;
}
