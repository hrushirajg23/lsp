/*

     Lseek system call is used to provide random access
     to a file rather than linear, it is used to file's position ine the file table
     
*/
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
//ssize_t ret,nr;
#define SIZE 1024
int len=1024;
char Buffer[SIZE];
int main(){
     int fd=open("kern.txt",O_RDWR );
     printf("file descriptor is %d\n",fd);
     if(fd==-1){
          perror("open");
          exit(EXIT_FAILURE);
     }
     char *buf="major minor device drivers to be written ";
     off_t ret;
     //off_t lseek(int fd,off_t pos,int origin);
     /*
     origin:
     SEEK_CUR:
          The curr file position is set to its current VALUE
          plus 'pos' which can be negative , zero or positive. 
          A pos==0 returns the current file position.
     
     SEEK_END:
          The curr file position is set to current LENGTH of file
          plus 'pos' which can be negativ , zero or positive.
          A pos==0 sets the offset to the end of file.

     SEEK_SET:
          The curr file position is set to 'pos'. A pos of 0 
          sets the offset to beginning of the file.

     The call returns the new file position on success. On error
     it returns -1.
     */
    off_t pos=0;
     if((pos=lseek(fd,0,SEEK_CUR))==-1){
          perror("lseek");
     }
     printf("Current position of offset is %ld\n",pos);
     ret=lseek(fd,(off_t)3,SEEK_SET);
     if(ret==(off_t)-1){
          perror("lseek");
          exit(EXIT_FAILURE);
     }
     if((pos=lseek(fd,0,SEEK_CUR))==-1){
          perror("lseek");
     }
     printf("Current position of offset is %ld\n",pos);
     puts("lseek done\n\n");
     int iRet=0;
     if((iRet=read(fd,Buffer,100))==-1){
          perror("read");
          exit(EXIT_FAILURE);
     }

     if((pos=lseek(fd,0,SEEK_CUR))==-1){
          perror("lseek");
     }
     printf("Current position of offset is %ld\n",pos);
     char *str="masala veg non veg";
     iRet=write(fd,str,strlen(str));
     if(iRet==-1){
          perror("write");
     }

       if((pos=lseek(fd,0,SEEK_CUR))==-1){
          perror("lseek");
     }
     printf("Current position of offset is %ld\n",pos);
     printf("\n%d bytes written\n",iRet);
     iRet=read(fd,Buffer,iRet);
     if(iRet==-1){
          perror("write");
     }

       if((pos=lseek(fd,0,SEEK_CUR))==-1){
          perror("lseek");
     }
     printf("Current position of offset is %ld\n",pos);
     printf("\n%d bytes read\n",iRet);
     for(int i=0;i<iRet;i++){
          printf("%c",Buffer[i]);
     }
     puts("\n\n");
     read(fd,Buffer+iRet,3);
      iRet=write(STDOUT_FILENO,Buffer,iRet);
     if(iRet==-1){
          perror("write");
     }
     
     puts("\n");
     //fsync(fd);  //to ensure data is succesfully written to disk
     // close(fd);
     lseek(fd,0,SEEK_END);
     pos=lseek(fd,0,SEEK_CUR);
     printf("current postion is %ld\n",pos);
     
     /*
     Lseeking beyond the file's position
     
     */
     iRet=lseek(fd,(off_t)188,SEEK_END);
     if(iRet==(off_t)-1){
          perror("lseek beyonnd end");
     }

     close(fd);
     puts("After closing of file------------------------------\n");
     fd=open("kern.txt",O_RDWR );
     printf("file descriptor is %d\n",fd);
     if(fd==-1){
          perror("open");
          exit(EXIT_FAILURE);
     }
     pos=0;
     if((pos=lseek(fd,0,SEEK_CUR))==-1){
          perror("lseek");
     }
     printf("Current position of offset is %ld\n",pos);
     return 0;
}