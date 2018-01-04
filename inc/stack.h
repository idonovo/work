
#ifndef __MYSTACK__
#define __MYSTACK__

#include "./ADTDefs.h"
#include "./double.h"
#include "./list_itr.h"


typedef struct Stack Stack;

Stack* StackCreate(void);

void StackDestroy(Stack** _stack, void (*_elementDestroy)(void* _item));

ADTErr StackPush(Stack* _stack, void*  _item);

ADTErr StackPop(Stack* _stack, void** _item);

ADTErr StackTop(Stack* _stack, void* _item);

int StackIsEmpty(Stack* _stack);

#endif  /*__MYSTACK__ */
