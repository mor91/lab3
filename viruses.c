#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
void printHex(char buffer[], int length){
    
    int i;
    for(i=0; i<length;i++)
    	printf("%02X ", buffer[i]);
    printf("\n");
}
void split(char buffer[], int length){
    int i=0;
    int j;
    int N;
    while(i<length){
	    char size[4];
	    memset(size,0,sizeof(size));
            int tempsize=i+4;
	    for(i; i<tempsize;i++)
	    	size[tempsize-4-i]=buffer[i];
	    N=convertToInt(size);
	    char signature[N]; 
            memset(signature,0,sizeof(signature));
            int tempN=N+i;
	    for( j=i ; j<tempN; j++)
		signature[j-i]=buffer[j];
	    i=j;
            char name[100]; 
            memset(name,0,sizeof(name));
	    for(j=i; buffer[j]!=0 ; j++)
		name[j-i]=buffer[j];
	    i=j+1;
	    printf("Virus name: %s\n", name);
	    printf("Virus size: %d\n", N);
            printf("signature:\n");
	    printHex(signature, sizeof(signature));
            printf("\n");
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
   int i;
   /*for(i=0 ;i<length ;i++){
   	printf("%c %d %02x\n", buffer[i], buffer[i], buffer[i]);
   }
   for(i=0 ;i<sizeof(buffer) ;i++){
   	printf("%c ", buffer[i]);
   }*/
   split(buffer, length);
   getchar();
   fclose(fp);
   return(0);
}

