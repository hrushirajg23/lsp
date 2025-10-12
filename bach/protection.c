#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<signal.h>
void sigcatcher(int);
void main(){

    int i,*ip;
    void function(void);
    


    ip=(int*)function();/*
    
        assigning addess of function to ip
    */
   void (*prev)(int)=NULL;
   for(i=0;i<20;i++){
        prev=signal(i,sigcatcher);
        prev(3);
   }

   *ip=1; /*
    attempt to overwrite address of function
    which is not possible as text section is 
    WRITE_PROTECTED , so overwriting sends a
    SIGBUS signal
   
   */
  puts("this is line after trying to overwrite function addr\n");
  function();
    exit(1);
}


void sigcatcher(int n){
    printf("n is %d\n",n);
}
void function(void){
    
}