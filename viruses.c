#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int convertToInt(char string[]){
	int len=strlen(string);
	int i;
	int res=0;
	for(i=0; i<len; i++)
		res=res*10+(string[i]-'0');
	return res;

}
/*void printHex(char buffer[], int length){
    int i;
    int N;
    int temp=0;
    while(temp<length){
	    char size[4];
	    memset(size,0,sizeof(size));
	    for(i=0; i<4;i++)
	    	size[i]=buffer[i];
	    N=convertToInt(size);
            printf("%d", N);
	    char signature[N]; 
	    for( i=4; i<N; i++)
		signature[i-4]=buffer[i];
	    char name[100];
	    for(i=N+4; buffer[i]!='\'; i++)
		name[i-N-4]=buffer[i];
	    printf("Virus name: %s\n", name);
	    printf("Virus size: %d\n", N);
	    printf("signature: %02x \n", signature);
	    temp+=i;
    }

}*/
int main(int argc, char* argv[])
{
   FILE *fp;
   unsigned char buffer[500];
   memset(buffer,0,sizeof(buffer));
   fp = fopen("signatures", "r");
   fseek(fp, 0, SEEK_SET);
   int length=fread(buffer, 1 ,sizeof(buffer), fp);
   int i;
   for(i=0 ;i<sizeof(buffer) ;i++){
   	printf("%c %d %02x\n", buffer[i], buffer[i], buffer[i]);
   }
   for(i=0 ;i<sizeof(buffer) ;i++){
   	printf("%c ", buffer[i]);
   }
   /*printHex(buffer, length);*/
   fclose(fp);
   return(0);
}

