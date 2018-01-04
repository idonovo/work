#include <stdio.h>
#include <stdlib.h>

#include "queue.h"



struct Queue

{

    int*    m_vec;

    size_t  m_size;   

    size_t  m_head;             

    size_t  m_tail;          

    size_t  m_nItems;     

};

/**********************************************/
static int HeadCalculate(Queue* _queue){
	
	if(_queue -> m_head == _queue -> m_size){
		return 0;
	} 
	return _queue -> m_head++;
}

static int TailCalculate(Queue* _queue){

	if(_queue -> m_tail == _queue -> m_size){
		return 0;
	} 
	return _queue -> m_tail++;

}

static int SpaceQueue(Queue* _queue){

	if (_queue->m_size == _queue->m_nItems){
		return 1;
	} 
	return 0;
}
/*********************************************/
Queue* QueueCreate(size_t _size){
	
	Queue* queue;
	
	if (_size < 1)
		{	
		 return NULL;
		}
	
	queue= malloc(sizeof(Queue));
	/* creating a pointer to the struct and dynamic array using malloc */
	if (queue == NULL)
		{	
		 return NULL;
		}
	queue->m_vec=malloc(_size*sizeof(int));
	
	if (queue == NULL)
		{
		 return NULL;
		}
		
	/* initial the struct */
	queue->m_size = _size;
	queue-> m_nItems = 0;
	queue-> m_head = 0;
	queue-> m_tail = 0;
	
	return queue;
}
/**********************************************/
void QueueDestroy(Queue* _queue){

	if(_queue != NULL)
	{
		free(_queue->m_vec);
	}
	free(_queue);
	return;
}
/**********************************************/
ADTErr QueueInsert(Queue* _queue, int _item){
	
	
	if (_queue == NULL || _queue->m_vec == NULL){
	
			return  ERR_NOT_INITIALIZED;
	}
	
	
	if (SpaceQueue(_queue) == 1){
	
			return ERR_OVERFLOW;
	}
	
	_queue->m_vec[(_queue->m_head)] = _item;
	_queue -> m_head == HeadCalculate(_queue);
	_queue->m_nItems++;

	return ERR_OK;
}
/**********************************************/
ADTErr  QueueRemove(Queue* _queue, int* _item){
	
	if(NULL ==_queue)
	{
		return ERR_NOT_INITIALIZED;
	}	
	
	if(NULL == _queue->m_vec)
	{
		return ERR_NOT_INITIALIZED;
	}		
	

	if(_item == NULL)
	{
		return ERR_NOT_INITIALIZED;		
	}
	
	if( 0 == _queue->m_nItems)
	{
		return  ERR_UNDERFLOW;		
	}
	
	
	_item = &_queue->m_vec[_queue->m_tail];
	_queue->m_vec[(_queue->m_tail)] = 0;
	
	_queue -> m_tail == TailCalculate(_queue);
	_queue->m_nItems--;
	
	return ERR_OK;
}
/**********************************************/
int QueueIsEmpty(Queue* _queue){
	
	if (_queue == NULL)
	{
		return 0;
	}
	
	if (_queue->m_vec == NULL)
	{
		return 0;
	}

	if(_queue->m_nItems != 0)
	{	
		return _queue->m_nItems;
	}
	
	return 0;
}

/**************************************************************/
void QueuePrint(Queue* _queue){

	int i = 0; 
	
	if(_queue == NULL)
	{
		printf("vector not valid");
	}
	
	for(i = _queue -> m_tail; i < _queue->m_nItems; i++)
	{
		printf("%d  ", _queue->m_vec[i%_queue->m_size]);
	
	}
	printf("\n");		
}














