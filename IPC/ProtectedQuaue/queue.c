#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>     

#include "queue.h"


#define FAIL -1
#define EMPTY 0

struct Queue
{
    void**  			m_vec;
    size_t  			m_size;   
    size_t  			m_head;             
    size_t  			m_tail;
    sem_t				m_full;
    sem_t				m_empty;
    pthread_mutex_t	m_mutex;
};

/*********************************************/
static void LocksDestroy(Queue* _queue);
/**********************************************/

Queue* QueueCreate(size_t _size){
	
	Queue* queue;
	pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	 
	if (_size < 1)
	{	
		 return NULL;
	}
	
	queue= malloc(sizeof(Queue));
	if (queue == NULL)
	{	
		 return NULL;
	}
	
	queue->m_vec=malloc(_size*sizeof(void*));
	if(queue == NULL)
	{
		free(queue);
		return NULL;
	}

	queue->m_mutex = mutex;
	
	if(FAIL == sem_init(&queue->m_full, 0, _size) || FAIL == sem_init(&queue->m_empty, 0, 0))
	{
		QueueDestroy(queue);
		return NULL;
	}
	
	queue->m_size = _size;
	queue-> m_head = 0;
	queue-> m_tail = 0;
	
	return queue;
}
/**********************************************/
void QueueDestroy(Queue* _queue){

	size_t i;
	
	if(NULL == _queue)
	{
		return;
	}
	
	if(NULL != _queue->m_vec)
	{
		free(_queue->m_vec);	
	}
	
	LocksDestroy(_queue);
	
	free(_queue);
	
	return;
}
/**********************************************/
ADTErr QueueInsert(Queue* _queue, void* _item)
{
	
	if(NULL == _queue  || NULL == _queue->m_vec || NULL == _item)
	{
		return  ERR_NOT_INITIALIZED;
	}
	    

  	sem_wait(&_queue->m_empty);
 	pthread_mutex_lock(&_queue->m_mutex);

	_queue->m_vec[(_queue->m_head)] = _item;
	_queue -> m_head = (_queue -> m_head +1)%_queue -> m_size;

	pthread_mutex_unlock(&_queue->m_mutex);
	sem_post(&_queue->m_full);
 
	return 0;
}
/**********************************************/
ADTErr  QueueRemove(Queue* _queue, void** _item)
{
	
	if(NULL ==_queue)
	{
		return ERR_NOT_INITIALIZED;
	}	
	
	if(NULL == _queue->m_vec)
	{
		return ERR_NOT_INITIALIZED;
	}		

	sem_wait(&_queue->m_full);
 	pthread_mutex_lock(&_queue->m_mutex);

	*_item = _queue->m_vec[_queue->m_tail];
	_queue -> m_tail = (_queue -> m_tail +1)%_queue -> m_size;

	pthread_mutex_unlock(&_queue->m_mutex);
	sem_post(&_queue->m_empty);
	
	return ERR_OK;
}

int QueueIsEmpty(Queue* _queue){
	
	int val;
	if (_queue == NULL || _queue->m_vec == NULL)
	{
		return 0;
	}

	sem_getvalue(&_queue->m_full, &val);

	return val == 0 ? 0 : 1;
}
/**********************************************/

static void LocksDestroy(Queue* _queue)
{
	if(&_queue->m_mutex)
	{
		pthread_mutex_destroy(&_queue->m_mutex);
	}
	
	if(&_queue->m_full)
	{
		 sem_destroy(&_queue->m_full);
	}
	
	if(&_queue->m_empty)
	{
		 sem_destroy(&_queue->m_empty);
	}
	return;
}








