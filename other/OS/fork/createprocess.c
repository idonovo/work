#include <stdio.h>
#include  <unistd.h>

int g_var = 0;

int main(){
	
	int i, n;
	int l_var = 0;
	
	n= fork();
	
	if(n < 0)
	{
		return -1;
	}
	else if(n > 0)
	{
		for (i = 0; i < 30; i++)
		{
			printf("father - %d\n", g_var+i);
			printf("father - %d\n", l_var+i);
			sleep(3);
		}
		
	}
	else
	{
		for (i = 0; i < 30; i++)
		{
			printf("child - %d\n", g_var-i);
			printf("child %d\n", l_var+i);
			sleep(1);
		}
	}
	
	return 0;
}
