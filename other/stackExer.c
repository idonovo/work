
#include <stdio.h>

int* ptr = NULL;


int Func(int _x)
{
    ptr = &_x;
    printf("value: %d Adress: 0x%x\n",*ptr, ptr);
    ptr -= sizeof(int);
    printf("value: %d Adress: 0x%x\n", *ptr, ptr);
    
    printf("Func value: %d Func Adress: 0x%x\n", *Func, Func);
    ptr -= sizeof(int);
    printf("value: %d Adress: 0x%x\n",*ptr, ptr);
    ptr -= sizeof(int);
    printf("value: %d Adress: 0x%x\n",*ptr, ptr);
    ptr -= sizeof(int);
    printf("value: %d Adress: 0x%x\n",*ptr, ptr);
    ptr -= sizeof(int);
    printf("value: %d Adress: 0x%x\n",*ptr, ptr);
    
	return _x;
}

int main(){
	
	
	Func(4);
	
	return 0;
}
