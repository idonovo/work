
#include <stdio.h>

int ReturnAbs(int _a)
{
	if(0 ==_a)
	{
	    return 0;
	}
	
	int comp =1;
	comp <<=sizeof(int)*8 -1;
	
	return _a & comp ? (~_a+1): _a;
}

void FromDecToHex(int _x){

	unsigned int curNum, i;
	unsigned int comp = 15;
	
	if (_x < 10)
	{
	    printf("%d", _x);
	}
	
	comp<<=sizeof(int)*7;	
		
		
	for(i =0; i<8; ++i)
	{	
		curNum = _x & comp;
		curNum >>=sizeof(int)*7;
		
		if(curNum < 10)
		{
			printf("%c", curNum + 48);
		}
		
		if(curNum >= 10 && curNum< 16)
		{
			printf("%c", curNum + 55);
		}
			
		_x<<=sizeof(int);
	}
	printf("\n");	
} 

int main(){
	
#pragma pack(push, 1)
struct Ed
{
	int x;
	char y;
	int a;
	char b;
};
#pragma pack(pop)

struct Ab
{
	int x;
	char y;
	int a;
	char b;
};

struct Cd
{
	int x;
	int a;
	char y;
	char b;
};

	

	
	printf("Ab =%u\n", sizeof(struct Ab));
	printf("Cd =%u\n", sizeof(struct Cd));
	printf("Ab after pragma =%u\n", sizeof(struct Ed));
	
	printf("absolute is %d\n", ReturnAbs(321));
	
	FromDecToHex(23423422);
	
	return 0;
}
