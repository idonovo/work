
#ifndef __MYQUEUE__
#define __MYQUEUE__

#include "ADTDefs.h"

typedef struct Queue Queue;
/* function to create a queue based on vector. the function recivies a fix size of the queue and returns a pointer to the struct qeuue*/
Queue* QueueCreate(size_t _size);
/* a finction to destroy a queue. the function recivies a pointer ti the the queue anf free all the allocted memory of the queue */
void QueueDestroy(Queue* _queue);
/* afunction to insert new items to the queue. the insertion rule is FIFO. if the queue if full the function return an overflow error*/
ADTErr QueueInsert(Queue* _queue, int _item);
/* afunction to remove items from the queue. the remove rule is FIFO. if the queue if empty the function return an underflow error*/
ADTErr QueueRemove(Queue* _queue, int* _item);
/* afunction to check wether the queue is empty. the function return 0 if the queue is empty or integer if it is not.*/
int QueueIsEmpty(Queue* _queue);
void QueuePrint(Queue* _queue);


#endif  /*__MYQUEUE__ */
