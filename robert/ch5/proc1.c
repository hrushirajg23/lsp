/*

    Get pid of current process
    and pid of current process's parent
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>


int main(){
    pid_t mine=getpid();
    pid_t parent=getppid();
    printf("My pid= %d\n",mine);
    printf("Parent pid= %d\n",parent);
    return 0;
}