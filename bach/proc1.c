/*
    Chapter 5 Bach

*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int fd_read,fd_write;
char ch;
void read_write(void);
pid_t procid;
int main(int argc,char* argv[]){
    
    if(argc!=3){
        puts("Need at least 3 args\n");
        exit(1);}
    if((fd_read=open(argv[1],O_RDONLY))==-1){
        exit(EXIT_FAILURE);
    }
    if((fd_write=open(argv[2],O_WRONLY | O_CREAT | O_APPEND))==-1){
        exit(EXIT_FAILURE);
    }
    procid=fork();

    read_write();
    return 0;
}

void read_write(void){
    for(;;){

        if(procid==0){
            puts("CHild process execturing\n");
        }
        else{
            puts("Parent executing\n");
        }
        if(read(fd_read,&ch,1)!=1){
            return ;
        }
        write(fd_write,&ch,1);
    }
}