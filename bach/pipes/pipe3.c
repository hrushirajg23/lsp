#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/wait.h>

int main(){

	int pipefd[2];
	pid_t cpid;
	char buf;
	if(pipe(pipefd)==-1){
		perror("pipe\n");
		exit(EXIT_FAILURE);
	}
	cpid=fork();
	if(cpid==-1){
		perror("fork\n");
		exit(EXIT_FAILURE);
	}
	if(cpid==0){	//child proc
		close(pipefd[1]);	
	
		while(read(pipefd[0],&buf,1)>0){
			write(STDOUT_FILENO,&buf,1);
		}
		write(STDOUT_FILENO,"\n",1);
		close(pipefd[0]);
	}
	else{
		close(pipefd[0]);
		const char* msg="hello , child process \n";
		write(pipefd[1],msg,strlen(msg));
		close(pipefd[1]);
		wait(NULL);
		exit(EXIT_SUCCESS);
	}

	return 0;
}