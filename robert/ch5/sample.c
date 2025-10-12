#include<stdio.h>

int main(int argc,const char* argv[]){


    printf("woaaaaaaaaaaaaaaaaaaaaaah\n");
    if(argc==0){
         printf("%s\n",argv[0]);
          printf("%s\n",argv[1]);
    }
    if(argc==1){
         printf("weird %s\n",argv[0]);
          printf("%s\n",argv[1]);
           printf("%s\n",argv[2]);
    }

   
    return 0;
}