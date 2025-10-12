#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/stat.h>
#include<string.h>
#include<sys/mman.h>


/*
     In blocking I/O, the read operation will cause 
     the program to wait until the input is available.

*/

char* blockingio(int fd){
     struct stat fs;
     fstat(fd,&fs);
     int size=fs.st_size;
     char* buffer=(char*)malloc(sizeof(char)*size);
     void *ptr;
     
     ptr=mmap()


     
}

int main(){

     char buffer[10];
     char mon[10];
     ssize_t bytes_read,from_file;
     int fd=open("default.txt",O_RDONLY);
     if(fd==-1){
          perror("Couldn't open file");
          return 1;
     }
     
     printf("Blocking I/O: Waiting for input...\n");


     /*this call will wait until data is available*/
     bytes_read=read(STDIN_FILENO,buffer,sizeof(buffer)-6);
     if(bytes_read==-1){
          perror("Error reading data\n");
          return 1;
     }
     printf("%zu bytes read\n",bytes_read);
     /*
          Jar apan terminal kade baghitla tar it is a file 
          only and its waiting for input
     */
     //fflush(stdin);
     from_file=read(STDIN_FILENO,mon,sizeof(buffer)-4);
     if(from_file==-1){
          perror("error reading data");
          return 1;
     }
     printf("%zu bytes read\n",from_file);
     buffer[bytes_read]='\0'; 
     printf("You entered %s\n",buffer);
    
     printf("in from file You entered %s\n",mon);

     char* str=blockingio(fd);

     return 0;
}