
#ifndef __MYSTACK__
#define __MYSTACK__

#include "enum.h"
#include "vector.h"
#include "stack.h"


typedef struct Stack Stack;

Stack* StackCreate( size_t _size, size_t _blockSize);

void StackDestroy(Stack* _stack);

ADTErr StackPush(Stack* _stack, int  _item);

ADTErr StackPop(Stack* _stack, int* _item);

ADTErr StackTop(Stack* _stack, int* _item);

int StackIsEmpty(Stack* _stack);

void StackPrint(Stack *_stack);


#endif  /*__MYSTACK__ */
