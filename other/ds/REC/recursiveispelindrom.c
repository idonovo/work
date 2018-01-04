#include <stdio.h>
#include <string.h>

int PelindromeRec(char* string, int size){

	initialsize = size;
	n = initialsize - size;
	
	if (size < 1 )
	{
		return;
	}
	
	PelindromeRec(string, size-1);
	
	if(string[n] == string[size])
	{
		printf("pelindrom");
	}
	
	
}
