#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>


void f(){
	printf("fork inside func with pid %d\n",getpid());

}
int main(){

	printf("woahhhhh %d\n",getpid());
	fork();
	f();
	printf("mahjong %d\n",getpid());

	return 0;
}
