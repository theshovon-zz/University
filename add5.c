#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
	FILE *fp1; 
	FILE *fp2 = fopen(argv[2], "w");
	char a[10];
	if ((fp1 = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "CAnt open %s \n", argv[1]);
		exit(EXIT_FAILURE);
		}
	fscanf(fp1,"%s", a);
	fprintf(fp2, "You have %s it", a );
	fclose(fp1);
	fclose(fp2);
return 0;
}
