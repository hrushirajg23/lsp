/*

    Sample programs of library calls
    atexit() and onexit() 
*/

/*

Using atexit() in this way ensures that you can perform important 
tasks or resource cleanup when your program terminates, regardless 
of how or why it terminates.

*/
/*

    on_exit(void (*function)(int,void*),void* arg);

    is same at atexit() except its first parameter(function pointer)
    points to  a function which accepts (int status,void* arg);
    The *status* is the value passed to exit() or return from main();
    The void* arg is similar to void* arg the second paramter

    on_exit is no longer standard




*/
#include<stdio.h>
#include<stdlib.h>

void out1(void){
    printf("atexit() succeded by out1\n");
}
void out2(void){
    printf("atexit() succeded by out2\n");
}

int main(){
    if(atexit(out1))
        fprintf(stderr,"atexit() failed\n");
    if(atexit(out2))
        fprintf(stderr,"atexit() failed\n");
    
    puts("Program is running... \n");

    puts("Program ended\n");
    _exit(0);
}