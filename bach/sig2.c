#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void sig_catcher(int);

int main(){
    int ppid;
    signal(SIGINT,sig_catcher);
    return 0;
}