
/*
    Two system calls are provided by linux for truncating length 
    of a file.

    1. int ftruncate(int fd, off_t len);

    2. int truncate(const char* path,off_t len);

    Both files must be writeable.

*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>


#define NRSIZE 45
char buff[NRSIZE];
int main(){

    int fd=0;
    if((fd=open("./pirate.txt",0666))==-1){
        perror("open\n");
        _exit(1);
    }
    read(fd,buff,NRSIZE);
    off_t pos=lseek(fd,(off_t)0,SEEK_CUR);
    printf("Current position of file is %d\n",(int)pos);
    // pos=lseek(fd,(off_t)20,SEEK_SET);
    // printf("Current position of file is %d\n",(int)pos);
    struct stat fsd;
    fstat(fd,&fsd);
    int iRet=ftruncate(fd,10);
    /*
        mhanje 10 bytes cha pudche sagle bytes udavle jatat
    */
    if(iRet==-1){
        puts("failed\n");
        exit(EXIT_FAILURE);
    }
    fsync(fd);
     pos=lseek(fd,(off_t)0,SEEK_CUR);
     printf("Current position of file is %d\n",(int)pos);
    puts("presenting file.....\n");
    while((iRet=read(fd,buff,NRSIZE))>0){
        write(STDOUT_FILENO,buff,iRet);
    }
    
    puts("\n");


    return 0;
}