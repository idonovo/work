
#include <stdio.h>

void Func(int _x){

	char y = 'X';
	char* a = &y;
	char** const ptr = &a;
	*ptr = y;
	
	printf("%c\n", *ptr);

}

int main(){

	int x = 10;
	
	Func(x);
	
	

}

