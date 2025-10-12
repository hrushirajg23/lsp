#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	int status;
	if(fork()==0)
		execl("./app","app",0);
	wait(&status);


	return 0;
}

