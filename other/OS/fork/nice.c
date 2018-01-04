#include <stdio.h>
#include <unistd.h>

int g_var = 0;

int main(){
	
	int i;

		nice();
		
		for (i = 0; i < 30; i++)
		{
			printf("mama - %d\n", g_var+i);
			sleep(3);
		}
	
	return 0;
}



