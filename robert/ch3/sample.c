#include<stdio.h>
#include<stdlib.h>

int main(void){
     FILE *in=NULL,*out=NULL;
     struct pirate{
          char name[100];
          unsigned long booty;     
          unsigned int beard_len;
     }p,blackbeard={"Edward Teach",950,48};
     
     out=fopen("data","w");
     if(!out){
          perror("fopen");
          return 1;
     }
     if(!fwrite(&blackbeard,sizeof(struct pirate),1,out)){
          perror("fwrite");
          exit(EXIT_FAILURE);
     }
     if(fclose(out)){
          perror("fclose");
          exit(EXIT_FAILURE);
     }
     in=fopen("data","r");
     if(!in){
          perror("fopen");
          return 1;
     }
     if(!fread(&p,sizeof(struct pirate),1,in)){
          perror("fread");
          return 1;
     }
     if(fclose(in)){
          perror("fclose");
          return 1;
     }

     printf("name=\"%s\" booty=%lu beard_len=%u\n",p.name,p.booty,p.beard_len);
     return 0;
}