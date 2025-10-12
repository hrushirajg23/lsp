/*
     When a call to write returns , the kernel has copied th data
     supplied from buffer into  a kernel buffer.
     BUT BUT theres is no guarantee that data has been written out to hard drive
     destination. 
*/

/*
     Inside the kernel , it gathers all the dirty buffers
     (buffers that contain data newer than what is on disk)
     sorts them optimally and writes them out to disk
     (this process is called as writeback)

*/

/*
1.   fsync system call ensures that all dirty data associated to the file
     is written to the disk . The call writes both data and metadata,such 
     file modfication time, and other attr of inode.

2.   fdatasync system call ensures that only data and metadata filesize
     is updated and other non-essential metadata like modf. time is not updated.
     Hence this call is potentially faster
*/


/*

     To be short
     fsync, fdatasync - synchronize a file's in-core state with
       storage device
*/


/*
     void sync(void)
     This system call synchronizes all buffers to disk
     It always succeeds. All data and meta data is written to disk

     Te O_SYNC flag used during open system call ensures the write system call if
     used later to perform synchronized I/O.
     (i.e it internally uses fsync)


     There a more 2 flags on Linux
     O_RSYNC and O_DSYNC

     O_DSNYC is similar to fdatasync() i.e the flag specifies that 
     only normal data be synchroized after each write operation
     not the metadata

     O_RSYNC synchronizes read requests as well. Though read reuqests
     are already synced , the flag tipulates that any side efects
     of read must also be synced such as meta data

*/


/*
     If some applications want to implement I/O mgmntof their own
     The O_DIRECT flag is used to initiate I/O directly from user-space
     buffers to device , bypassing the page cache. All I/O will be synchronous 
     and will take time.


*/


#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
ssize_t ret,nr;

int len=1024;

int main(){
     int fd=open("kern.txt",O_WRONLY);
     if(fd==-1){
          perror("open");
          exit(EXIT_FAILURE);
     }
     char *buf="major minor device drivers to be written ";
     while(len!=0 && (ret=write(fd,buf,len))!=0){
          if(ret==-1){
               if(errno==EINTR)
                    continue;
               perror("write");
               break;
          }
          len-=ret;
          buf+=ret;
     }
     fsync(fd);  //to ensure data is succesfully written to disk
     close(fd);
     return 0;
}