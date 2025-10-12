#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

char string[]="Hello world!";

int main(){
    int count ,i;
    int Parentpipes[2],Childpipes[2];
    char buffer[256];
    pipe(Parentpipes);
    pipe(Childpipes);
    if(fork()==0){
        puts("Child process executing\n");
        close(0); //close stdin
        dup(Childpipes[0]); /*stdin will become child's read pipe*/

    /*
    
   this example, fd 0 now means Childpipes[0] (the read end of a pipe),
    not the original stdin (which typically points to the terminal). 
    */
        close(1);
        dup(Parentpipes[1]); /*stdout will become Parent's write pipe*/

        /*
            Closing unnecessary file descs
        */
       close(Parentpipes[0]);
        close(Parentpipes[1]);
        close(Childpipes[1]);
        close(Childpipes[0]);
    
        for(;;){
            if((count=read(0,buffer,sizeof(buffer)))<1){
                exit(1);
            }
            write(1,buffer,count);
        }
    } 
    else{
        /*
        This is parent process execution
    */
    close(1);   /*close stdout*/
    dup(Childpipes[1]); /*stdout(not the terminal but the pipe end) will become child's write pipe*/
    close(0);           /*close stdin*/
    dup(Parentpipes[0]);    /*stdin(not the terminal but the pipe end) will become parent's read pipe*/

    close(Parentpipes[0]);
        close(Parentpipes[1]);
        close(Childpipes[1]);
        close(Childpipes[0]);
    
    for(i=0;i<15;i++){
        write(1,string,strlen(string));
        count=read(0,buffer,sizeof(buffer));
        buffer[count]='\0';
        printf("Parent received : %s\n",buffer);
    }
    }
    

    return 0;
}