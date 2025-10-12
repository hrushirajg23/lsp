#include<sys/mman.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/wait.h>

int main(){
     size_t size=4096;
     int fd=open("weird.txt",O_RDWR | O_CREAT |O_APPEND,0666);
     //Create a memory mapped region
     void* arr=mmap(NULL,size,PROT_READ | PROT_WRITE ,MAP_PRIVATE ,fd,0);
     if(arr==MAP_FAILED){
          perror("mmap");
          exit(EXIT_FAILURE);
     }
     strcpy((char*)arr,"Jensen Huang CEO of Nvidia\n");
     if(madvise(arr,size,MADV_DONTFORK)==-1){
          perror("madvise");
          return 1;
     }
     pid_t pid=fork();
     if(pid==-1){
          perror("fork");
          munmap(arr,size);
          return 1;
     }
     else if(pid==0){
          puts("Child process trying to read mapped memory \n");
          printf("%s : ",(char*)arr);
     }
     else{
          wait(NULL);
          puts("Parent process : memory private and safe from child access\n");

     }

     if(munmap(arr,size)==-1){
          perror("munmap");
          return 1;
     }
     return 0;
}