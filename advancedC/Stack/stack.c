#include <stdlib.h>

#include "../../inc/double.h"
#include "../../inc/stack.h"

#define MAGIC 0xddd

#define IS_A_STACK(s) ((s) && (s)->m_magic == MAGIC) 

struct Stack
{
    size_t m_magic;
    List *m_list;
};


Stack* StackCreate(void){

	/* create a pointer to the stack and if malloc succeed asign a vector pointer to the stack */
	Stack* stack;
	stack= malloc(sizeof(Stack));
	
	if (NULL == stack)
	{
		return NULL;
	}
	
	stack->m_list = ListCreate();
	
	if (NULL == stack->m_list)
	{
		free(stack);
		return NULL;
	}
	stack->m_magic = MAGIC;
	
	return stack; 
}
/*********************************************/

void StackDestroy(Stack** _stack,  void (*_elementDestroy)(void* _item)){
	
	if(!IS_A_STACK(*_stack))
	{
		return  ;
	}
	
	ListDestroy(&((*_stack)->m_list), _elementDestroy);
	(*_stack)->m_magic = 0;
	free(*_stack);
	*_stack = NULL;
	free(_stack); 
	return;	
}


/**********************************************/
ADTErr StackPush(Stack* _stack, void*  _item){

	if(!IS_A_STACK(_stack))
	{
		return  ERR_NOT_INITIALIZED;
	}

	if(_item == NULL)
	{
		return  ERR_NOT_INITIALIZED;
	}
	
	if(LIST_OK != ListPushTail(_stack->m_list, _item))
	{
		return ERR_REALLOCATION_FAILED;	
	}
	
	return ERR_OK;
	
}

/**********************************************/
ADTErr StackPop(Stack* _stack, void** _item){

	
	if(!IS_A_STACK(_stack))
	{
		return  ERR_NOT_INITIALIZED;
	}
	
	if(_item == NULL)
	{
		return  ERR_NOT_INITIALIZED;
	}
	
	if(ListIsEmpty(_stack->m_list))
	{
		return  ERR_UNDERFLOW;
	}
	
	if(ListPopTail(_stack->m_list, _item) != LIST_OK)
	{
		return ERR_REALLOCATION_FAILED;
	}

	return ERR_OK;
}

/**********************************************/
ADTErr StackTop(Stack* _stack, void* _item){
	
	if(!IS_A_STACK(_stack))
	{
		return  ERR_NOT_INITIALIZED;
	}
	
	if(_item == NULL)
	{
		return  ERR_NOT_INITIALIZED;
	}
	
	if(ListIsEmpty(_stack->m_list))
	{
		return  ERR_UNDERFLOW;
	}
	
	_item =  (void*)ListItr_End(_stack->m_list);
	
	return ERR_OK;
}

/**********************************************/
int StackIsEmpty(Stack* _stack){

	if(!IS_A_STACK(_stack))
	{
		return  1;
	}
	
	return ListIsEmpty(_stack->m_list);

}

/**************************************************************/

