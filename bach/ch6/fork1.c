#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int fdrd, fdwt;
char c;

void rdwrt();

void main(argc, argv)
    int argc;
    char *argv[];
{
    if(argc != 3)
        exit(1);
    if((fdrd = open(argv[1], O_RDONLY)) == -1)
        exit(1);
    if((fdwt = creat(argv[2], 0666)) == -1)
        exit(1);
    
    fork();

    /* both procs execute same code */

    rdwrt();
    exit(0);
}

void rdwrt()
{
    for(;;){
        if(read(fdrd, &c, 1) != 1)
            return;
        write(fdwt, &c, 1);
    }
}
