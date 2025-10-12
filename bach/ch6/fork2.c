#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 256

char string[] = "hello world";

int main(void)
{

    int count, i = 0;
    char buf[BUF_SIZE];
    int child[2];
    int parent[2];

    pipe(parent);
    pipe(child);

    if(fork() == 0){

        close(0);
        dup(child[0]);
        close(1);
        dup(parent[1]);

        close(parent[0]);
        close(parent[1]);
        close(child[0]);
        close(child[1]);

        for(;;){
            if((count = read(0, buf, BUF_SIZE)) == 0){
               exit(0);
            }
            write(1, buf, count);
        }
    }

    close(1);
    dup(child[1]);
    close(0);
    dup(parent[0]);

    close(parent[0]);
    close(parent[1]);
    close(child[0]);
    close(child[1]);

    for (i = 0; i < 15; i++){
        write(1, string, strlen(string));
        read(0, buf, BUF_SIZE);
    }

    return 0;
}
