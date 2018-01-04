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
    size_t 				m_nItems;  
   	pthread_cond_t 		m_emptyCond;
   	pthread_cond_t 		m_fullCond;
    pthread_mutex_t		m_mutex;
};

/**********************************************/
Queue* QueueCreate(size_t _size){
	
	Queue* queue;
	pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
	pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
	 
	if (_size == EMPTY)
	{	
		 return NULL;
	}
	
	queue= malloc(sizeof(Queue));
	if (queue == NULL)
	{	
		 return NULL;
	}
	
	queue->m_vec = malloc(_size*sizeof(void*));
	if(queue == NULL)
	{
		free(queue);
		return NULL;
	}

	queue->m_mutex = mutex;
	queue->m_emptyCond = cond1;
	queue->m_fullCond = cond2;
	queue->m_size = _size;
	queue-> m_head = 0;
	queue-> m_tail = 0;
	queue-> m_nItems = 0;
	
	return queue;
}
/**********************************************/
void QueueDestroy(Queue* _queue){
	
	if(NULL == _queue)
	{
		return;
	}
	
	if(NULL != _queue->m_vec)
	{
		free(_queue->m_vec);	
	}
	
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
	
 	pthread_mutex_lock(&_queue->m_mutex);
 	
 	while(_queue->m_size ==_queue-> m_nItems)
 	{
 		pthread_cond_wait(&_queue->m_emptyCond, &_queue->m_mutex);
 	}
 	 
	_queue->m_vec[(_queue->m_head)] = _item;
	_queue -> m_head = (_queue -> m_head +1)%_queue -> m_size;
	++_queue-> m_nItems; 
	
	pthread_cond_signal(&_queue->m_fullCond);
	
	pthread_mutex_unlock(&_queue->m_mutex);

	return 0;
}
/**********************************************/
ADTErr QueueRemove(Queue* _queue, void** _item)
{
	
	if(NULL ==_queue || NULL == _queue->m_vec)
	{
		return ERR_NOT_INITIALIZED;
	}	

 	pthread_mutex_lock(&_queue->m_mutex);
 	
 	while(EMPTY ==_queue-> m_nItems)
 	{
 		pthread_cond_wait(&_queue->m_fullCond, &_queue->m_mutex);
 	} 

	*_item = _queue->m_vec[_queue->m_tail];
	_queue -> m_tail = (_queue -> m_tail + 1)% _queue -> m_size;
	--_queue-> m_nItems;
	
	pthread_cond_signal(&_queue->m_emptyCond); 
	pthread_mutex_unlock(&_queue->m_mutex);
	
	return ERR_OK;
}

/**********************************************/
int NumOfItems(Queue* _queue)
{
	
	if (_queue == NULL || _queue->m_vec == NULL)
	{
		return 0;
	}

	return _queue-> m_nItems;
}








