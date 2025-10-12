#include<stdio.h>
#include<stdlib.h>
#include<sys/uio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<assert.h>

/*
     vectored i/o cha upyog kay
     Mhanje jar mala 50 strings lihayche astil eka file var, tar instead 
     of 50 system calls to write , i'll only make one system call to writev()

     powerful



*/
int main(){
     int num_seg=0;
     printf("Enter the number of data segments\n");
     scanf("%d",&num_seg);

     struct iovec* iov=(struct iovec*)malloc(sizeof(struct iovec)*num_seg);
     assert(iov);
     fflush(STDIN_FILENO);
     getchar();
     for(int i=0;i<num_seg;i++){
          printf("Enter a string for index %d\n",i);
          char* buffer=NULL;
          size_t len=0;
          ssize_t readlen=getline(&buffer,&len,stdin);
          if(readlen==-1){
               perror("failed to read line\n");
               exit(EXIT_FAILURE);
          }
          if(buffer[readlen-1]=='\n'){
               buffer[readlen-1]='\0';
               readlen--;
          }
          iov[i].iov_base=(void*)buffer;
          iov[i].iov_len=readlen;
     }

     int fd=open("output.txt",O_WRONLY | O_CREAT | O_APPEND ,0644);
     if(fd==-1){
          perror("failed open");
          exit(EXIT_FAILURE);
     }

     //write all strings to file using writev()
     ssize_t written=writev(fd,iov,num_seg);
     if(written==-1){
          perror("write failed\n");
          exit(EXIT_FAILURE);
     }
     else{
          printf("successfully written %zd bytes \n",written);
     }

     for(int i=0;i<num_seg;i++){
          free(iov[i].iov_base);
     }
     free(iov);
     close(fd);

     return 0;
}
