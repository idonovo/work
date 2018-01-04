#ifndef __MYVECTOR__
#define __MYVECTOR__

#include <stddef.h>
#include "enum.h"

typedef struct Vector Vector;

Vector* VectorCreate(size_t _initialSize, size_t _extensionBblockSize);

void VectorDestroy(Vector* _vector);

ADTErr VectorAdd(Vector *_vector,  int  _item); 

ADTErr VectorDelete(Vector *_vector,  int* _item); 

ADTErr VectorGet(Vector *_vector, size_t _index, int *_item);

ADTErr VectorSet(Vector *_vector, size_t _index, int  _item);

ADTErr VectorItemsNum(Vector *_vector, size_t*  _numOfItems);

void VectorPrint(Vector *_vector);


#endif  /*__MYVECTOR__*/
