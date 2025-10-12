/*
    sample program using setpgrp() 
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>

/*
    Now this program creates 10 child process having smilar group 
    to parent but odd numbered processes change their group but executing
    setpgrp() again , Thus kill(0,SIGINT) which is suppose send signal
    to all 10 process in its group sends to onyl 5 as other 5 have changed 
    their group.

*/
void sigHandle(int sig){
    printf("Signal recevied for process id: %d and group: %d\n",getpid(),getpgrp());
}
/*
    Now the odd numbered child processes get stucked due 
    to pause and as they don't get SIGNAL they keep waiting 
    for signal .

*/

void faulty(){
    register int i;

    pid_t x=setpgrp();
    for(i=0;i<10;i++){
        if(fork()==0){
            /*
                Child process
            */
            if(signal(SIGINT,sigHandle)==SIG_ERR){
                perror("error in signal \n");
                exit(EXIT_FAILURE);
            }
            if(i & 1) /*evaluates to i%2!=0 only odd numebrs*/
            {       
                setpgrp();
            }
            printf("pid == %d , pgrp = %d\n",getpid(),getpgrp());
            pause(); /*suspend process until signal is received*/
        }
    }
    kill(0,SIGINT);

}


void correct(){
    register int i;
    pid_t x=setpgrp();
    pid_t parr[10];
    for(i=0;i<10;i++){
        parr[i]=fork();
        if(parr[i]==0){
            /*
                Child process
            */
            if(signal(SIGINT,sigHandle)==SIG_ERR){
                perror("error in signal \n");
                exit(EXIT_FAILURE);
            }
            if(i & 1) /*evaluates to i%2!=0 only odd numebrs*/
            {       
                setpgrp();
            }
            printf("pid == %d , pgrp = %d\n",getpid(),getpgrp());
            pause(); /*suspend process until signal is received*/
            exit(0);
        }
    }
    for(i=0;i<10;i++){
        kill(parr[i],SIGINT);
    }
}
int main(){
    faulty();
    correct();
    return 0;
}


