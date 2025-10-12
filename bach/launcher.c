#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>


int main(){
	int status;
	execl("/bin/vim","vim","zeta.txt",NULL);
	//wait(&status);
	return 0;
}
