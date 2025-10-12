#include<stdio.h>
#include<stdint.h>
struct test{
     __uint32_t events;
     union{
          void* ptr;
          int fd;
          __uint32_t u32;
          __uint64_t u64;
     }data;
};

int main(){
     int n=100;
     unsigned char* cpr=NULL;
     struct test t1;
     t1.data.ptr=&n;
     int* p=&t1.data.fd;
     printf("p points to address %u\n",p);
     printf("p points to address %u\n",&t1.data.ptr);
     printf("p points to address %u\n",&t1.data.u32);
     printf("p points to address %u\n",&t1.data.u64);

     cpr=(*(unsigned char*)(&t1.data.fd));
     printf("Address is %ld n is : %d\n",&t1.data.ptr,*((int*)(t1.data.ptr)));
     
     printf("Data of n is : %d\n",((*cpr)));
     
     //printf("Data of n is %d : %d\n",(int)(t1.data.fd),);
     printf("size of t1 is %ld\n",sizeof(t1));
     return 0;
}