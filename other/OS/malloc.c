
# include <stdlib.h>
# include <stdio.h>

int main(){

	char* ptr;
	unsigned int x = 1024, i = 0;
	
	
	while (ptr !=NULL){
	
		ptr =  malloc((x*1024)*sizeof(char));
		++i;
	}
	
	printf("%d\n", i);	

}
