#include<stdio.h>
#include<stdlib.h>

struct Node{
     int data;
     struct Node* next;
};

void addhead(struct Node** head,int data){
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



int writelist(FILE* fp,struct Node* head){
     while(head!=NULL){
          if((fwrite(head,sizeof(struct Node),1,fp))<1){
               puts("error writing file\n");
               return -1;
          }
          head=head->next;
     }
     return 1;
}

void addnode(struct Node** head,struct Node* newn){
     //struct Node* newn=(struct Node*)malloc(sizeof(struct Node));
     if(*head==NULL){
          *head=newn;
     }
     else{
          newn->next=(*head);
          (*head)=newn;
     }
}

int readlist(FILE* fp, struct Node** head) {
    size_t iRet = 0;
    struct Node* newn = NULL;

    // Initialize the head to NULL if it is not already
    *head = NULL;

    while (1) {
        newn = malloc(sizeof(struct Node));
        if (!newn) {
            // Handle malloc failure
            perror("malloc");
            return -1;
        }

        iRet = fread(newn, sizeof(struct Node), 1, fp);
        if (iRet != 1) {
            // Free the last allocated node if it was not added to the list
            free(newn);
            break;
        }
        // Ensure the new node's next pointer is set to NULL
        newn->next = NULL;
        printf("newn data is %d\n", newn->data);
        addnode(head, newn);
    }

    if (feof(fp)) {
        return 1; // Success
    } else {
        return -1; // Read error
    }
}

int readlistfromend(FILE* fp,struct Node** head){
    size_t nodesize=sizeof(struct Node);
    struct Node* newn=NULL;
    long filepos;

    if(fseek(fp,0,SEEK_END)==-1){
          perror("fseek");
          return -1;
    }
    filepos=ftell(fp); //getting current position of stream file
    if(filepos==-1)
    {
          perror("ftell");
          return -1;
    }

    while(filepos>=nodesize){
          newn=malloc(nodesize);
          if(!newn){
               perror("malloc");
               return -1;
          }
          filepos-=nodesize;
          if(fseek(fp,filepos,SEEK_SET)==-1){
               perror("fseek");
               free(newn);
               return -1;
          }

          if(fread(newn,nodesize,1,fp)!=1){
               perror("fread");
               free(newn);
               return -1;
          }

          newn->next=NULL;

          printf("newn data is %d\n",newn->data);
          addnode(head,newn);
    }
    return 1;
}

void display(struct Node* head){
     while(head!=NULL){
          printf("| %d |->",head->data);
          head=head->next;
     }
     puts("NULL\n");
}

int main(void){
     struct Node* First=NULL;
     struct Node* bridge=NULL;
     struct Node* end=NULL;
     addhead(&First,50);
     addhead(&First,40);
     addhead(&First,30);
     addhead(&First,20);
     addhead(&First,10);

     FILE* fp=NULL;
     fp=fopen("banana","a+");
     if(!fp){
          perror("fopen");
          return 1;
     }
     // if(writelist(fp,First)==-1){
     //      puts("writing errror\n");
     //      exit(EXIT_FAILURE);
     // }
     if(readlist(fp,&bridge)==-1){
          puts("reading errror\n");
          exit(EXIT_FAILURE);
     }
     display(bridge);

      if(readlistfromend(fp,&end)==-1){
          puts("reading errror\n");
          exit(EXIT_FAILURE);
     }
     display(end);
     fclose(fp);
     return 0;
}