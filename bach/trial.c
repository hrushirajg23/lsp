#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>

int jojo=11;
FILE* fptr;

void conv(char (*ptr)[3],register int i){
	memset(*ptr,'0',3);
	int s=2;
	while(i!=0 && s>=0){
		(*ptr)[s--]=i%10+'0';
		i/=10;
	}
}

int main(){
	int fd=open("junk.txt",O_WRONLY | O_TRUNC);
	close(fd);
	puts("Entered parent......\n");
	fptr=fopen("junk.txt","a+");
	
	if(!fptr){
		puts("call failed\n");
		_exit(1);
	}
	fseek(fptr,0,SEEK_SET);
	int status;
	int xy;
	int zx=4;;
	pid_t p1=fork();
	if(p1==0){
		//execl("/bin/vim","vim","zeta.txt",NULL);
		puts("\nENTERED child........\n");
		//zx++,jojo++;
		char str[3];
		for(register int i=0;i<300;i++){
		//printf("Printing by pid:  %d with ppid: %d\n",getpid(),getppid());
			str[3]='\0';
			conv(&str,i);
			fputs(str,fptr);
			
			fputs("CHILD\n ",fptr);	
			//sleep(1);
	//	printf("jojo is %d,zx is %d \n",jojo,zx);	
		}
		//fclose(fptr);
		//_exit(0);
	}
	char str[3];
	for(register int i=0;i<300;i++){
		//printf("jojo is %d,zx is %d \n",jojo,zx);	
		conv(&str,i);
		fputs(str,fptr);
		fputs("PARENT\n",fptr);
		
		//printf("Printing by pid:  %d with ppid: %d\n",getpid(),getppid());
	}
	fclose(fptr);
	wait(&status);
	return 0;
}


/*
	

*/