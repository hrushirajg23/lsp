#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

struct Node{
     int data;
     struct Node* next;
};
void addFirst(struct Node** head,int data){
     struct Node* newn=(struct Node*)malloc(sizeof(struct Node));
     newn->data=data;
     newn->next=NULL;

     if(*head==NULL){
          *head=newn;
     }
     else{
          newn->next=(*head);
          (*head)=newn;
     }


}
int main(){

     int fd=0;
     // struct stat st;
     // if((fd=open("war.exe",O_WRONLY | O_CREAT ,S_IRUSR | S_IWUSR |S_IRGRP|S_IWGRP|S_IWOTH|S_IROTH))==-1){
     //      perror("open war");
     //      exit(EXIT_FAILURE);
     // }
     //printf("mode of file is %d\n",(int)st.st_gid);
     FILE* fptr=fopen("war","a+");
     if(fptr==NULL){
          perror("failed opening ");
          exit(EXIT_FAILURE);
     }
     struct Node* First=NULL;
     addFirst(&First,50);
     addFirst(&First,40);
     addFirst(&First,30);
     addFirst(&First,20);
     addFirst(&First,10);
     
     struct Node* trav=First;
     while(trav!=NULL){
          if(!fwrite(&(trav->data),sizeof(trav->data),1,fptr)){
               perror("fwrite\n");
               exit(EXIT_FAILURE);
          }
          trav=trav->next;
     }
    // struct Node* newn=(struct Node*)malloc(sizeof(struct Node));
     int data;
     rewind(fptr);
     while((fread(&data,sizeof(data),1,fptr))==1)
     {
          printf("%d-> ",data);
     }
     puts("NULL\n");

     fclose(fptr);
     return 0;
}