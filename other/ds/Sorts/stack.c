#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "stack.h"

struct Stack

{

    Vector *m_vector;

};

/*********************************************/
Stack* StackCreate(size_t _size, size_t _blockSize){

	/* create a pointer to the stack and if malloc succeed asign a vector pointer to the stack */
		Stack* stack;
		stack= malloc(sizeof(Stack));
		
		if (NULL == stack){
		 return NULL;
		}
		
		stack->m_vector = VectorCreate(_size, _blockSize);
		
		if (stack->m_vector == NULL ){
		 	return NULL;
		}
		
		
		return stack; 
}
/*********************************************/

void StackDestroy(Stack* _stack){

	int i;
	
	if(_stack == NULL){
	
		printf("No Valid stack");
	
	}
	/* calling vectordestroy and then free the stack */
	VectorDestroy(_stack->m_vector);
	free(_stack);
 
	
	
}


/**********************************************/
ADTErr StackPush(Stack* _stack, int  _item){

	ADTErr flag;
	
	if (_stack == NULL){
	
		return  ERR_NOT_INITIALIZED;
	}
	
	
	flag = VectorAdd(_stack->m_vector, _item);
	
	return flag;
	
}

/**********************************************/
ADTErr StackPop(Stack* _stack, int* _item){

	ADTErr flag;
	
	if (_stack == NULL){
	
		return  ERR_NOT_INITIALIZED;
	}
	
	
	flag = VectorDelete(_stack->m_vector, _item);
	
	return flag;
}

/**********************************************/
ADTErr StackTop(Stack* _stack, int* _item){
	
	size_t *ptr;
	ADTErr flag;
	
	if (_stack == NULL){
	
		return  ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum(_stack->m_vector, ptr);
	

	flag = VectorGet(_stack->m_vector, *ptr, _item);
	
	return flag;
	

}

/**********************************************/
int StackIsEmpty(Stack* _stack){

	size_t ptr;
	ADTErr flag;
	
	VectorItemsNum(_stack->m_vector, &ptr);
	
	
	if (_stack == NULL || _stack->m_vector == NULL ||  ptr == 0){
	
		return  1;
	}
		
	return 0;

}

/**************************************************************/
void StackPrint(Stack *_stack){

	if (_stack == NULL){
	
		printf("ERR_NOT_INITIALIZED");
	}
	
	VectorPrint(_stack->m_vector);

}


/**************************************************************/


