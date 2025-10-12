/*
    Working of fork + execv

*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>




int main(){
    pid_t pid;

    pid=fork();
    if(pid==-1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(pid==0){
        char* const args[]={"myexe",NULL};
        int iRet=0;
        iRet=execv("./myexe",args);
        if(iRet==-1){
            perror("execv");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
