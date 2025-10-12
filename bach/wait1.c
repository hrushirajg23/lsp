#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<signal.h>


void handler(int g){
    printf("Executing handler for pid %d\n",getpid());
}
int main(int argc,char* argv[]){
    
    int i,ret_val,ret_code;
    if(argc>1){
        signal(SIGCHLD,handler);
    }
    for(i=0;i<20;i++){
        if(fork()==0){
            printf("child's process ID = %d\n",getpid());
            exit(i);
        }
         ret_val=wait(&ret_code);
    printf("wait ret_val= %d AND ret_code = %d\n",ret_val,ret_code);
    
    }
    ret_val=wait(&ret_code);
    printf("wait ret_val= %d AND ret_code = %d\n",ret_val,ret_code);
    return 0;
}
