#include<stdio.h>
#include<sys/syscall.h>

int main(void){
	int limit, div, i, count;
	printf("Enter the limit: ");
	scanf("%d", &limit);
	for(i = 2; i<=limit; i++){
		count=0;
		for(div=2; div <=i; div++){
			if(i%div == 0){
			count++;
			}
			
		}
		if(count==1){
		printf("%d \n",i);
		}
	}	

return 0;
}
