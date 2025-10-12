#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>


/*
When the kernel invokes a signal handler, it passes the number of the signal that
caused the invocation as an integer argument to the handler. 
(This is the sig argument in the handler sigHandle ).
*/
static void sigHandle(int sig){

	printf("Ouch with sig: %d\n",sig);
}
int main(){

	int j;
	if(signal(SIGINT,sigHandle)==SIG_ERR)
		perror("signal");
		
	// if(signal(SIGQUIT,sigHandle)==SIG_ERR)
	// 	perror("signal");
	/*
		Above stmt Causes havoc
	
	*/
	for(j=0;;j++){
	
		printf("%d\n",j);
		sleep(3);	/*loop slowly*/
	}


	return 0;
}
