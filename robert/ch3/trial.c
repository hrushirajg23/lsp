#include<stdio.h>

int a_glob;
int b_glob=11;
static int d_glob=32;
int main(){
    static int e_loc=42;
    int c_loc=21; 
    printf("Hello world\n");
    return 0;
}