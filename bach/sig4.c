#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
/* Establishing the same handler for two different signals
*/
static void sigHandle(int sig){
    static int count=0;
    /* UNSAFE: This handler uses non-async-signal-safe functions
(printf(), exit(); see Section 21.1.2) */
    if(sig==SIGINT){
        count++;
        printf("Caught SIGINT (%d)\n",count);
        return;
    }
    /* Must be SIGQUIT - print a message and terminate the process */
    if(sig==SIGQUIT ){
        printf("Caught SIGQUIT - (%d) that's all folks!\n");
        exit(EXIT_SUCCESS);
    }
}


int main(){
    if(signal(SIGINT,sigHandle)==SIG_ERR)
        exit(EXIT_FAILURE);
    if(signal(SIGQUIT,sigHandle)==SIG_ERR)
        exit(EXIT_FAILURE);
    
    for(;;)/*Loop forever ,waiting for signals*/
        pause();    /*suspends the process until a signal arrives*/
    
    return 0;
}