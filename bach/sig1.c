#include<stdio.h>
#include<signal.h>
#include<unistd.h>


void catcher(int sg){
	printf("Signal %d caught \n",sg);

}


int main(){
	signal(SIGINT,catcher);
	printf("Send a signal using Ctrl+C ....\n");
	while(1){
	
		sleep(1);	//waiting for signal
	}
	

	return 0;
}
