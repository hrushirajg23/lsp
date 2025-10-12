#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/select.h>

#define BUFFER_SIZE 256

int main() {
    int count;
    int Parentpipes[2], Childpipes[2];
    char buffer[BUFFER_SIZE];
    
    pipe(Parentpipes); // Parent to Child
    pipe(Childpipes);  // Child to Parent

    if (fork() == 0) {  // Child process
        close(Parentpipes[0]); // Child won't read from Parentpipes[0] (parent's read pipe)
        close(Childpipes[1]);  // Child won't write to Childpipes[1] (child's write pipe)
        
        for(;;) {
            // Child reads from the parent (Childpipes[0] is for reading parent's messages)
            count = read(Childpipes[0], buffer, sizeof(buffer) - 1);
            if(count > 0) {
                buffer[count] = '\0'; // Null-terminate received string
                printf("Child received: %s\n", buffer);
            }
            
            // Child sends message to parent
            printf("Child: ");
            fgets(buffer, BUFFER_SIZE, stdin); // Get input from child
            write(Parentpipes[1], buffer, strlen(buffer));
        }
    } else {  // Parent process
        close(Parentpipes[1]); // Parent won't write to Parentpipes[1] (child's write pipe)
        close(Childpipes[0]);  // Parent won't read from Childpipes[0] (parent's read pipe)
        
        for(;;) {
            // Parent reads from the child (Parentpipes[0] is for reading child's messages)
            count = read(Parentpipes[0], buffer, sizeof(buffer) - 1);
            if(count > 0) {
                buffer[count] = '\0'; // Null-terminate received string
                printf("Parent received: %s\n", buffer);
            }

            // Parent sends message to child
            printf("Parent: ");
            fgets(buffer, BUFFER_SIZE, stdin); // Get input from parent
            write(Childpipes[1], buffer, strlen(buffer));
        }
    }
    
    return 0;
}
