#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<signal.h>

int main(){
    int uid,euid,fd_flower,fd_fruit;
    uid=getuid();
    euid=geteuid();
    printf("uid= %d  AND euid= %d\n",uid,euid);
    fd_flower=open("flower.txt",O_RDONLY);
    fd_fruit=open("fruit.txt",O_RDONLY);
    printf("fd_flower= %d  AND fd_fruit= %d\n",fd_flower,fd_fruit);
    /*
    calling setuid()
    
    */
   /*
    Set the user ID of the calling process to UID.
If the calling process is the super-user, set the real
and effective user IDs, and the saved set-user-ID to UID;
if not, the effective user ID is set to UID.
   
   */
    setuid(uid);

    printf("after calling first setuid(%d): uid=%d AND euid= %d\n",uid,getuid(),geteuid());
    fd_flower=open("flower.txt",O_RDONLY);
    fd_fruit=open("fruit.txt",O_RDONLY);
    printf("fd_flower= %d  AND fd_fruit= %d\n",fd_flower,fd_fruit);
    setuid(euid);

     printf("after calling first setuid(%d): uid=%d AND euid= %d\n",uid,getuid(),geteuid());
    
    return 0;
}