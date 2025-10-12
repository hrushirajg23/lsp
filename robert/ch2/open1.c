#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<unistd.h>

int main(){
	int fd1=open("/mnt/data/LSP/ch2/default.txt",0644);
	if(fd1==-1){
		perror("Couldn't open file because\n");
	}
	ssize_t ret;
	char buffer[1024];
	int len=1024,size=1024;
	while(len!=0 && (ret=read(fd1,buffer,len))!=0){
		if(ret==-1)
		{
			if(errno==EINTR)
				continue;
			perror("read");
			break;
		}
		for(int i=0;i<ret;i++){
			printf("%c",buffer[i]);
		}
		len-=ret;
	//	buffer+=ret;
	}
//	while((ret=read(fd1,buffer,sizeof(buffer)))!=-1){
//		for(int i=0;i<ret;i++){
//			printf("%c",buffer[i]);
//		}
//
//	}


	


	return 0;
}
