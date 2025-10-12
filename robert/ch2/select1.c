/*
    Assume you're waiting for input from a file but it is still empty
    and this could go on forever blocking the process and cpu. 
    Because many times you have requests coming from many clients
    and you cannot afford spending time waiting for input fo a long time.


    Hence we use select() which gets a set of file_descriptors 
    that are to be checked , when ready informs the process 
    This helps cpu be used for other tasks until data is written to
    file and process getting unblocked.
*/
#include<sys/select.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

int main(){

    int fd=0;
    fd=open("pirate.txt",O_CREAT | O_RDONLY,0666);
    char buff[20];
    read(fd,buff,20);
    return 0;
}