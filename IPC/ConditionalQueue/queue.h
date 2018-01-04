
#ifndef __MYQUEUE__
#define __MYQUEUE__

#include <stdlib.h>
#include "ADTDefs.h"

typedef struct Queue Queue;

Queue* QueueCreate(size_t _size);

void QueueDestroy(Queue* _queue);

ADTErr QueueInsert(Queue* _queue, void* _item);

ADTErr  QueueRemove(Queue* _queue, void** _item);

int NumOfItems(Queue* _queue);

#endif  /*__MYQUEUE__ */


	
