#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#define SIZE 256
char buffer[SIZE];
int main(){
    int fd;
    int iRet=0;
    fd=open("very.txt", O_RDONLY );
    if(fd==-1){
        perror("open");
        exit(EXIT_FAILURE);

    }
    
    /*
        blocking mode but since there is no data
    */
    while((iRet=read(fd,buffer,SIZE))>0){
        printf("%ld bytes read: %s\n",iRet,buffer);
    }

    if(iRet==-1){
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    
   // printf("%d printing...... %s\n",iRet,buffer);
    close(fd);
    fd=open("very.txt", O_NONBLOCK | O_RDONLY );
    if(fd==-1){
        perror("open");
        exit(EXIT_FAILURE);

    }
    again:
    iRet=read(fd,buffer,SIZE);
    printf("%ld bytes read: %s\n",iRet,buffer);
    if(iRet==-1){
        if(errno==EAGAIN || EINTR){
            goto again;
        }
        else{
            perror("error reading \n");
            exit(EXIT_FAILURE);
        }
    }



    return 0;
}