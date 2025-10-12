#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<string.h>
#define SIZE 512
char Buffer[SIZE];
int main(){
	int iRet=0;
	int fd;
	off_t offset;
	if((fd=open("test.txt",O_RDWR))==-1){
		perror("Couldn't open file");
		exit(EXIT_FAILURE);		
	}
	
	offset=lseek(fd,-8,SEEK_END);
	if((iRet=read(fd,Buffer,SIZE))==-1){
		perror("error reading");
		exit(EXIT_FAILURE);
	}

	printf("Current offset is %ld\n",offset);
		
	offset=lseek(fd,0,SEEK_CUR);

	printf("Current offset is %ld\n",offset);
		
	puts("reading data\n");
	for(int i=0;i<iRet;i++){
		printf("%c",Buffer[i]);
	}
	const char* str="angelina";
	if(write(fd,str,strlen(str))==-1){
		puts("Couldn't write data");
		exit(EXIT_FAILURE);
	}
	offset=lseek(fd,0,SEEK_CUR);
	printf("Current offset is %ld\n",offset);
	puts("truncating ....\n");
	if((iRet=truncate("./test.txt",strlen(str)))==-1){
		perror("truncate");
		return -1;
	}
	printf("Current offset is %ld\n",offset);
		

	return 0;
}



