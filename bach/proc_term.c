
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
void sigHandle(int sig){
    puts("handling sig");

}

 
int main(){
    pid_t pid;

    
  __sighandler_t handler;
 handler=sigHandle; 

   handler(SIGINT);
    // pid=fork();
    // if(pid==0){
    //     exit(1);
    // }
    // else{
    //     exit(0);
    // }
    
    return 0;
}