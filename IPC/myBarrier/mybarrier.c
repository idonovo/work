
#include <stdlib.h>
#include <pthread.h>     

#include <unistd.h>  
#include <time.h>     
#include "mybarrier.h"

#define EMPTY 0
#define SUCCESS 0
#define SHUT_DOWN 1
#define FAIL -1

struct Barrier
{
    size_t		 		m_capacity;
    size_t				m_counter;
    size_t				m_attendance;
    size_t				m_shutDownflag; 
    pthread_mutex_t		m_mutex;
	pthread_cond_t 		m_condVar;
	pthread_cond_t 		m_destCondVar;
};

Barrier* BarrierCreate(size_t _capacity)
{
	Barrier* newBarrier = NULL;
	
	if(EMPTY == _capacity)
	{
		return NULL;
	}
	
	newBarrier = malloc(sizeof(Barrier));
	if(!newBarrier)
	{
		return NULL;
	}
	
	pthread_cond_init(&newBarrier->m_condVar, NULL);
	pthread_mutex_init(&newBarrier->m_mutex, NULL);
	pthread_cond_init(&newBarrier->m_destCondVar, NULL);
	newBarrier->m_capacity = _capacity;
	newBarrier->m_attendance = EMPTY;
	newBarrier->m_counter = EMPTY;
	newBarrier->m_shutDownflag = EMPTY;
	
	return newBarrier;
}

void BarrierDestroy(Barrier* _barrier)
{
	if(!_barrier)
	{
		return;
	}
	
	pthread_mutex_lock(&_barrier->m_mutex);
	_barrier->m_shutDownflag = SHUT_DOWN;
	pthread_mutex_unlock(&_barrier->m_mutex);
	pthread_cond_broadcast(&_barrier->m_condVar); 
	
	while(EMPTY != _barrier->m_attendance)
	{
		pthread_cond_wait(&_barrier->m_condVar, &_barrier->m_mutex);
	} 

	pthread_mutex_destroy(&_barrier->m_mutex);
	pthread_cond_destroy(&_barrier->m_condVar);
	free(_barrier);
	
	return;
}

int BarrierWait(Barrier* _barrier)
{
	if(!_barrier)
	{
		return FAIL;
	}
	
	if(SHUT_DOWN == _barrier->m_shutDownflag)
	{
	    return (int)_barrier->m_shutDownflag;
	}
	
	pthread_mutex_lock(&_barrier->m_mutex);
	
 	++_barrier->m_counter;
 	
 	if(_barrier->m_counter != _barrier->m_capacity && SHUT_DOWN != _barrier->m_shutDownflag) 
 	{
 		++_barrier->m_attendance;
 		pthread_cond_wait(&_barrier->m_condVar, &_barrier->m_mutex);
 		--_barrier->m_attendance;
 	}
 	else
 	{
		_barrier->m_counter = EMPTY;
		pthread_cond_broadcast(&_barrier->m_condVar);
 	} 
	pthread_mutex_unlock(&_barrier->m_mutex);
	
	if(EMPTY == _barrier->m_attendance)
	{
		pthread_cond_broadcast(&_barrier->m_destCondVar);
	}
	
	return (int)_barrier->m_shutDownflag;
}
