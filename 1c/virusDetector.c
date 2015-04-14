
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct virus virus;
	 
	struct virus {
		int length;
		char *signature;
		char *name;
		virus *next;
};
void printHex(char buffer[], int length){
    
    int i;
    for(i=0; i<length;i++)
    	printf("%02X ", buffer[i]);
    printf("\n");
}

void print_data(virus *virus_node){
    printf("name: %s\n", virus_node->name);
    printf("length: %d\n", virus_node->length);
    printf("signature: \n");
    printHex(virus_node->signature, virus_node->length); 
    printf("\n");
}

void list_print(virus *virus_list){
    if(virus_list!=NULL){
        virus *tempVirus=virus_list;
        print_data(tempVirus);
        while (tempVirus->next!=NULL){
            tempVirus=tempVirus->next;
            print_data(tempVirus);
        }
    }
}
virus *list_append(virus *virus_list, virus *data){
    if(virus_list!=NULL){
        virus *tempVirus=virus_list;
        while(tempVirus->next!=NULL){
            tempVirus=tempVirus->next;
        }
        tempVirus->next=malloc(sizeof(virus));
        tempVirus->next=data;
    }
    else {
        virus_list=malloc(sizeof(virus));
        virus_list=data;
    }
    return virus_list;
}
void list_free(virus *virus_list){
    if(virus_list!=NULL){
        virus *tempVirus=virus_list;
        virus *nextVirus=virus_list;
        while(tempVirus->next!=NULL){
            nextVirus=tempVirus->next;
            free(tempVirus->name);
            free(tempVirus->signature);
            tempVirus=nextVirus;     
        }
    }
}



int power(int num1, int num2){
    int i;
    int j=1;
    for(i=0; i<num2 ;i++){
        j*=num1;
    }
    return j;
}

int convertToInt(char string[]){
	int len=strlen(string);
	int i;
	int res=0;
	for(i=0; i<len; i++){
		res=res+(power(256,i)*string[i]);        
        }
	return res;

}

virus* split(char buffer[], int length){
    virus* virus_list=NULL;
    int i=0;
    int j;
    int N;
    while(i<length){
	    char * size = malloc(sizeof(char)*4);;
	    memset(size,0,sizeof(size));
            int tempsize=i+4;
	    for(i; i<tempsize;i++)
	    	size[tempsize-4-i]=buffer[i];
	    N=convertToInt(size);
	    char * signature = malloc(sizeof(char)*N);; 
            memset(signature,0,sizeof(signature));
            int tempN=N+i;
	    for( j=i ; j<tempN; j++)
		signature[j-i]=buffer[j];
	    i=j;
            char * name = malloc(sizeof(char)*100); 
            memset(name,0,sizeof(name));
	    for(j=i; buffer[j]!=0 ; j++)
		name[j-i]=buffer[j];
	    i=j+1;
            virus* virus=NULL;
            virus=malloc(sizeof(virus));
            /*virus->length=malloc(sizeof(int));*/
            virus->length=N;
            virus->signature=malloc(sizeof(signature));
            virus->signature=signature;
            virus->name=malloc(sizeof(name));
            virus->name=name;
            virus->next=NULL;
            virus_list=list_append(virus_list, virus);
    }
    return virus_list;

}
void printDetect(int i,char name[], int size){
    printf("Infected file!\n");
    printf( "starting byte location in the file: %d\n", i);
    printf("The virus name: %s\n", name);
    printf("The size of the virus: %d\n", size);
    
}
void detect_virus(char *buffer, virus *virus_list, unsigned int size){
    int i;
    virus* tempVirus=virus_list;
    int isInfected=0;
    for(i=0;i<size;i++){
        while(!isInfected){
            if(memcmp(tempVirus->signature, &buffer[i], tempVirus->length)==0){
                printDetect(i, tempVirus->name, tempVirus->length);
                isInfected=1;
            }
            if(tempVirus->next!=NULL)
                tempVirus=tempVirus->next;
            else break;
        }
        tempVirus=virus_list;   
    }
}
int main(int argc, char* argv[])
{
   FILE *fp;
   unsigned char buffer[500];
   memset(buffer,0,sizeof(buffer));
   fp = fopen("signatures", "r");
   fseek(fp, 0, SEEK_SET);
   int length=fread(buffer,1, sizeof(buffer) , fp);
   virus* virus_list;
   virus_list=split(buffer, length);
   unsigned char bufferfile[10000];
   memset(bufferfile,0,sizeof(bufferfile));
   FILE *file;
   file=fopen("infected","r");
   fseek(fp, 0 ,SEEK_SET);
   int filesize=fread(bufferfile,1, sizeof(bufferfile) , file);
   unsigned int size;
   if(filesize< sizeof(bufferfile))
       size=filesize;
   else size=sizeof(bufferfile);
   detect_virus(bufferfile, virus_list, size);
   fclose(fp);
   fclose(file);
   list_free(virus_list);
   
   getchar();
   return(0);
}



