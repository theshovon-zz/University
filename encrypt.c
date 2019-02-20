#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 80
//-------------------------------------------------------------------------------------
int main(int argc, char *argv[]){
	int key = atoi(argv[2]);
	if((argc < 3)) {
		fprintf(stderr, "Usage: encrpyt filename Key\n");
		exit(EXIT_FAILURE);
	}
	if(key < 1 || key > 25 ){
		fprintf(stderr, "Key should be an integer between 1 to 25 inclusive\n");
		exit(EXIT_FAILURE);	
	}

		char msg[N];
		char *msgout= argv[1] ;
		 int i = 0;
		int c;

		FILE *fpin = fopen(argv[1], "r");
		FILE *fpout;
		if (fpin==NULL){
		fprintf(stderr, "Can't open %s\n", argv[1]);
		exit(EXIT_FAILURE);
		} 
        	fpout = fopen(strncat(argv[1],".enc",4), "w");
		if (fpout==NULL){
		fprintf(stderr, "Can't open %s\n", argv[1]);
		exit(EXIT_FAILURE);
		} 
		while(!feof(fpin)){
			fgets(msg, N, fpin);
		}
		char temp;
		for (i=0; i <= strlen(msg); i++) {
        		if (isalpha (msg[i])) {
    				if (islower(msg[i])) {
       					 temp = ((msg[i] - 'a') + key) % 26 + 'a';
       					 //printf("%c", temp);
					putc(temp,fpout);
       				}
   				else{
        				temp = ((msg[i] - 'A') + key) % 26 + 'A';
        				//printf("%c", temp);
					putc(temp,fpout);
        			}
			}else{
				//printf("%c", msg[i]);
				putc(msg[i],fpout);
			}
   		 }
fclose(fpin);
fclose(fpout);
	
return 0;
}

