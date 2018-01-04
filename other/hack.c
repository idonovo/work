#include <stdio.h>

int ptr;

int Hack(int _y)
{
	printf("you hacked!!\n");
	*(&_y-1) = ptr;
	return 0;
}


int Func(int _x)
{
    int i=8;
    int y=8;
    printf("in foo\n");
	ptr = *(&_x -1);
   	*(&_x - 1) = Hack;
   	
   	printf("Adress: %p value: %d\n",&i, i);
   	for(y=1; y<8; y++)
   	{
   		printf("Adress: %p value: %p value: %d\n",&_x-y, *(&_x-y), *(&_x-y));
   	}
    
	return 0;
}

int main(){
	
	int n = 6;
	printf("Adress n: %p value n: %d\n",&n, n);
	Func(n);
	
	return 0;
}
