#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define _GNU_SOURCE
int main(int argc, char *argv[]) {
    struct stat sb;
    off_t len;
    char *p;
    int fd;

    if (argc < 2) {
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    if (fstat(fd, &sb) == -1) {
        perror("fstat");
        return 1;
    }

    if (!S_ISREG(sb.st_mode)) {
        fprintf(stderr, "%s is not a file\n", argv[1]);
        return 1;
    }

    /*
    
    MAP_PRIVATE does not reflect changes to file or in mappings of other processes 
    whereas 
    MAP_SHARED does and also all processes sharing the
    mapping witness the reflect changes 
    */
    p = mmap(0, sb.st_size, PROT_WRITE | PROT_READ , MAP_PRIVATE, fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap");
        return 1;
    }


    /*
        A call made to msync(void* addr,size_t len,int flags),
        flushes back to disk any changes made to file mapped via mmap(),
        synchronising the mapped file with the mapping. Synchronizes len 
        bytes from addr to disk.

    
    */
    if(msync(p,sb.st_size,MS_ASYNC)==-1){
        perror("msync");
    }

    printf("Size of file is %zd\n", sb.st_size);

    puts("Resizing...\n");

    // Adjusting the size to allocate more memory
    // size_t new_size = sb.st_size + BUFSIZ;
    // void *ptr = mremap(p, sb.st_size, new_size, MREMAP_MAYMOVE);
    // if (ptr == MAP_FAILED) {
    //     perror("mremap");
    //     return 1;
    // }

    // // Update the size to the new one after resizing
    // sb.st_size = new_size;
    // p = ptr;

   // printf("New size of file is %zd\n", sb.st_size);

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    // Display the content of the resized memory
    for (len = 0; len < sb.st_size; len++) {
        p[len]-=1;
        putchar(p[len]);
    }

    if (munmap(p, sb.st_size) == -1) {
        perror("munmap");
        return 1;
    }

    return 0;
}
