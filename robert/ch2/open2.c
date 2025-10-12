

/*

     int open(const char* name,int flags,mode_t mode)
     The mode paramter in the open system call is only used when 
     O_CREAT flag is used , i.e when creating a new file 
     the mode is used to give permission to it.
     The mode argument is ignored unless O_CREAT is specified

*/
/*

     Due to umask = 022
     If we give permission 0666
     it will get reduced to 0644 i.e 0666-0022
     umask is a default mask for protection of permission on systems
     it can be modified , in my device its 0002
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(){
     
     mode_t old_mask = umask(0); // Get the current umask
    umask(old_mask); // Reset it back to what it was

    printf("Current umask: %04o\n", old_mask); // 
     int fd;
     fd=open("kern.txt",O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR | S_IWGRP |S_IRGRP | S_IROTH);
     /*
     similar to 

     fd=open("kern.txt",O_WRONLY | O_CREAT | O_TRUNC,0664);
     */
    // fd=open("weird.txt",O_WRONLY | O_CREAT | O_TRUNC,0644);
     if(fd==-1)
     {
          perror("Couldn't open file \n");
          exit(EXIT_FAILURE);
     }
     
     return 0;
}