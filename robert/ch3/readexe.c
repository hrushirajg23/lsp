#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

int main(){
    struct stat buf;
    int iRet=stat("./app",&buf);
    if(iRet==-1){
        printf("Couldn't get file\n");
        exit(EXIT_FAILURE);
    }
    size_t size=buf.st_size;
    FILE* fptr=fopen("app","r");
    if(fptr==NULL){
         printf("Couldn't read file\n");
        exit(EXIT_FAILURE);
    }
    char* ptr=malloc(sizeof(char)*(size+1));
    ptr[size]='\0';

    size_t read_bytes=fread(ptr,sizeof(char),size,fptr);
    printf("%u bytes read\n",read_bytes);
    if(read_bytes==0 || read_bytes==EOF){
        printf("Failed in reading\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<=size;i++){
        printf("%c",ptr[i]);
    }
    return 0;
}