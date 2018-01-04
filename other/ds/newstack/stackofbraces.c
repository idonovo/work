
#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "stack.h"


int CheckBraces(char* string)
{

	int i;
	int size = 50;
	int blocksize = 50;
	int stringLength;
	
	Stack* stack;
	stack= malloc(sizeof(Stack));
	StackCreate(size, blocksize);
	int braces;
	stringLength = strlen(string);
	
	do{
		
		if(string[i] == '(' || string[i] == '[' || string[i] == '{')
		{
			StackPush(stack, string[i]);
		}
		
		if(string[i] == ')') 
		{
			StackTop(stack, &braces);
			if(braces != '(')
			{
				StackDestroy(stack);
				return 1;
			}
		}	
		if(string[i] == ']') 
		{
			StackTop(stack, &braces);
			if(braces != '[')
			{
				StackDestroy(stack);	
				return 1;
			}
		}				
				
		if(string[i] == '}') 
		{
			StackTop(stack, &braces);
			if(braces != '{')
			{
				StackDestroy(stack);
				return 1;
			
			}
		}								
		i++;			
	}while(i<stringLength);

	if(StackIsEmpty(stack) != 0)
	{
		StackDestroy(stack);
		return 1;
	}

}
