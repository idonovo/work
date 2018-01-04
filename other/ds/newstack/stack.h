
#ifndef __MYSTACK__
#define __MYSTACK__

#include "./ADTDefs.h"
#include "./vector.h"

typedef struct Stack Stack;

typedef int	(*VectorElementAction)(void* _element, void* _context);

Stack* StackCreate( size_t _size, size_t _blockSize);

void StackDestroy(Stack* _stack, void (*_elementDestroy)(void* _item);

ADTErr StackPush(Stack* _stack, void*  _item);

ADTErr StackPop(Stack* _stack, void** _item);

ADTErr StackTop(Stack* _stack, void** _item);

int StackIsEmpty(Stack* _stack);

#endif  /*__MYSTACK__ */
