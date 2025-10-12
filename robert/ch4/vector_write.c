

/*
     A simple program that demonstrates use of writev() system
     call to write out a vector of 3 segments , each containing 
     a string of different size. 


*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/uio.h>
#include<unistd.h>

int main(void){
     struct iovec iov[3];
     ssize_t nr;
     int fd,i;

     char* buf[]={
          "The term buccaneer comes from the word boucan\n",
          "A boucan is a wooden frame used for cooking meat\n",
          "Buccaneer is the West Indies name for a pirate\n"
     };
     
     if((fd=open("buccaneer.txt",O_WRONLY | O_CREAT | O_TRUNC,0666))==-1){
          perror("open");
          return 1;
     }
     /*
          fill out three iovec structures
     */
     for(i=0;i<3;i++){
          iov[i].iov_base=buf[i];
          iov[i].iov_len=strlen(buf[i]);
     }
     if((nr=writev(fd,iov,3))==-1){
          perror("writev");
          return 1;
     }
     
     printf("wrote %ld bytes \n",nr);
     if(close(fd)){
          perror("close");
          return 1;
     }
     return 0; 
}