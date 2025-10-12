#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<elf.h>
#include<elfutils/elf-knowledge.h>
#include<signal.h>
#include<a.out.h>
#include<sys/mman.h>
#include<sys/stat.h>
#define __GNU_EXEC_MACROS__




int fd=0;
   
#define BSIZE 1024
char buffer[BSIZE];

void catcher (int x){
    puts("received signal\n");
    kill(getpid(),SIGQUIT);
}



void identify_seg(const Elf64_Phdr* seg){
    Elf64_Word word=seg->p_type;
    switch(word)
    {
        case 0x00000000:
            printf("NULL segment\n");
        break;
        case 0x00000001:
            printf("Loadable segment\n");
        break;
        case 0x00000002:
            printf("Dynamic Linking info segment\n");
        break;
        case 0x00000003:
            printf("Interpreter info segment\n");
        break;
        case 0x00000004:
            printf("Auxiliary info segment\n");
        break;
        case 0x00000005:
            printf("Reserved segment\n");
        break;
        case 0x00000006:
            printf("Program header segment\n");
        break;
        case 0x00000007:
            printf("Thread storage segment\n");
        break;
         case 0x60000000:
            printf(" Reserved OS specific segment\n");
        break;
         case 0x6fffffff:
            printf("Reserved OS specific segment\n");
        break;
         case 0x70000000:
            printf("Reserved Processor specific segment\n");
        break;
         case 0x7fffffff:
            printf("Reserved Processor specific segment\n");
        break;
        
    }
}
void read_prog_header(char* file,unsigned long len,Elf64_Ehdr* ehdr){
    Elf64_Phdr phdr;
    char* p=file+ehdr->e_phoff;
    int i=0;
   // Elf64_Phdr* temp=phdr;
   FILE* fptr=fopen("text_read.txt","w+");
   FILE* fptr2=fopen("data_read.txt","w+");
   if(fptr==NULL){perror("fopen\n");return;}
    for(i=0;i<ehdr->e_phnum;i++){
        phdr=*(Elf64_Phdr*)p;
        printf("seg %d resides at offset %lu having filesize %lx\n",i,phdr.p_offset,phdr.p_filesz);
        identify_seg(&phdr);
        if(phdr.p_type==PT_LOAD){
            puts("Loading.....\n");
            char* ptr=file+phdr.p_offset;
            printf("This segment resides at %lu in memory & has %lu size in memory & %lu size in elf\n",phdr.p_vaddr,phdr.p_memsz,phdr.p_filesz);
        //  puts("loading data.........\n");
            if((phdr.p_flags&PF_R) && (phdr.p_flags& PF_X)){
                puts("this is text segment\n");
                 fwrite(ptr,sizeof(char),phdr.p_filesz,fptr);
            }
            else if((phdr.p_flags& PF_R ) && ((phdr.p_flags& PF_W ))){
                puts("this is data segment\n");
                fwrite(ptr,sizeof(char),phdr.p_filesz,fptr2);
            }

          
           // for(int i=0;i<phdr.p_filesz;i++){
                //printf("%c",ptr+i);
               
            //}
            puts("\n");
        }
        p+=sizeof(Elf64_Phdr);
        
    }

    fclose(fptr);
    fclose(fptr2);
}

void print_section_details(char* file,int index,Elf64_Shdr* shdr,Elf64_Ehdr* ehdr){
    // for(register int i=0;i<sizeof(shdr->sh_name);i++){
    //     printf("%c",*(char*)&shdr->sh_name+1);
    // }
    int flags=shdr->sh_flags;
    char* str=NULL;
    switch(flags){
        case 0x01:
            str="WRITE ONLY";
            break;
        case 0x02:
            str="ALLOC ONLY";
            break;
        case 0x03:
            str="WRITE+ALLOC";
            break;
        case 0x04:
            str="EXEC ONLY";
            break;
        case 0x05:
            str="WR + EXEC";
            break;
        case 0x06:
            str="ALLOC + EXEC";
            break;
        case 0xf0000000:
            str="MASK PROC";
            break;
        default:
            str="something else";
            break;
    }
    printf("name: %d & flags: %s & size: %x & address is: %lu\n",shdr->sh_name,str,shdr->sh_size,shdr->sh_addr);
    if(shdr->sh_flags==0x06){
        printf("loading executable section at offset %lu\n",shdr->sh_offset);
        FILE* fptr=NULL;
        fptr=fopen("text_read.txt","w+");
        if(fptr==NULL){perror("fopen\n");return;}
        char* ptr=file+shdr->sh_offset;
        fwrite(ptr,sizeof(char),shdr->sh_size,fptr);
        fclose(fptr);
    }
    if(shdr->sh_type==3){
        puts("this section contains the string table\n");
        for(int i=0;i<shdr->sh_size;i++){
            printf("%c",file+shdr->sh_addr);
        }
    }
    puts("\n");
   

}
void read_sec_header(FILE* fptr,char* file,unsigned long len,Elf64_Ehdr* ehdr){
    Elf64_Shdr shdr;
     puts("--------------Section header info---------------\n");
    printf("Section header offset is %lu\n",ehdr->e_shoff);
    printf("Section header size is %d\n",ehdr->e_shentsize);
    printf("Number of Section header entries are %d\n",ehdr->e_shnum);
    
    char* ptr=file+ehdr->e_shoff;
    for(int i=0;i<ehdr->e_shnum;i++){
        shdr=*(Elf64_Shdr*)ptr;
        printf("Entry %d :  ",i);
        print_section_details(file,i,&shdr,ehdr);
        ptr+=sizeof(Elf64_Shdr);
    }

    // int nr_elements=fread(&shdr,sizeof(Elf64_Shdr),)
}

int main(){
    FILE* fptr=NULL;
    signal(SIGSEGV,catcher);
    FILE* fw=NULL,*saver=NULL;
    struct stat st;
    Elf64_Ehdr header;
    int fd=open("./app",O_RDONLY);
    fstat(fd,&st);
    if((fptr=fopen("./app","a+"))==NULL){
        perror("couldn't read file");
        exit(1);
    }
    
    char* p=mmap(0,st.st_size,PROT_READ ,MAP_SHARED,fd,0);
    if(p==MAP_FAILED){
        perror("mmap");
        exit(1);
    }
    header=*(Elf64_Ehdr*)p;
    puts("putting magic \n");
    for(int i=0;i<4;i++){
        if(i==0){
            printf("%d \t",header.e_ident[i]);
        }
        else{
            printf("%c\t",header.e_ident[i]);
        }
    }
    
    printf("elf header size is %d\n",header.e_ehsize);
    printf("entry address is %lu\n",header.e_entry);


    puts("--------------Program header info---------------\n");
    printf("Program header offset is %lu\n",header.e_phoff);
    printf("Program header size is %d\n",header.e_phentsize);
    printf("Number of Program header entries are %d\n",header.e_phnum);
    


   // read_sec_header(fptr,p,st.st_size,&header);
    read_prog_header(p,st.st_size,&header);
    close(fd);
    fclose(fptr);
    // fclose(saver);
    // fclose(fw);
    if(munmap(p,st.st_size)==-1){
        perror("munmap");
        return 1;
    }
    return 0;
}

