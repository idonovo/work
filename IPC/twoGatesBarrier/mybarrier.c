
#include <stdlib.h>
#include <pthread.h>     
#include <unistd.h>  
#include <stdio.h>    
#include "mybarrier.h"

#define EMPTY 0
#define SUCCESS 0
#define SHUT_DOWN 1
#define GATE_OPEN 1
#define GATE_CLOSE 0

#define FAIL -1

struct Barrier
{
	pthread_cond_t 		m_waitingRoomVar;
	pthread_cond_t 		m_insideCondVar;
    pthread_mutex_t		m_mutex;
    unsigned int		m_capacity;
    unsigned int		m_counter;
    unsigned int		m_waitingRoomCounter;
    unsigned int		m_shutDownflag;
    unsigned int		m_numOfBatches;
    unsigned int		m_curBatch;
    unsigned int		m_firstGateMode; 
    unsigned int		m_secondGateMode;  
};

/*********************************************************************/
static void WaitOnFirstGate(Barrier* _barrier);

static void OpenFirstGate(Barrier* _barrier);

static void WaitOnSecondGate(Barrier* _barrier, actionFunc _actionFunc, void* _context);

static void OpenSecondGate(Barrier* _barrier, actionFunc _actionFunc, void* _context);

static unsigned int SetID(Barrier* _barrier);

static unsigned int SetBatch(Barrier* _barrier);
/*********************************************************************/

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
		goto BARRIER;
	}

	if(SUCCESS != pthread_cond_init(&newBarrier->m_waitingRoomVar, NULL))
	{
		goto DESTROYWAITINGBARRIER;
	}
	
	if(SUCCESS != pthread_cond_init(&newBarrier->m_insideCondVar, NULL))
	{
		goto DESTROYINSIDECONDVAR;
	}
	
	if(SUCCESS != pthread_mutex_init(&newBarrier->m_mutex, NULL))
	{
		goto DESTROYMUTEX;
	}
	
	newBarrier->m_capacity = _capacity;
	newBarrier->m_waitingRoomCounter = EMPTY;
	newBarrier->m_counter = EMPTY;
	newBarrier->m_shutDownflag = EMPTY;
	newBarrier->m_numOfBatches =  EMPTY;
	newBarrier->m_curBatch =  EMPTY; 
	newBarrier->m_firstGateMode = GATE_CLOSE; 
    newBarrier->m_secondGateMode = GATE_CLOSE;
	return newBarrier;
		
DESTROYMUTEX:
	pthread_mutex_destroy(&newBarrier->m_mutex);		 
DESTROYINSIDECONDVAR:
	pthread_cond_destroy(&newBarrier->m_waitingRoomVar);
DESTROYWAITINGBARRIER: 
	pthread_cond_destroy(&newBarrier->m_waitingRoomVar);	
BARRIER: 
	return NULL;
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

	pthread_mutex_destroy(&_barrier->m_mutex);
	pthread_cond_destroy(&_barrier->m_waitingRoomVar);
	free(_barrier);
	
	return;
}

int BarrierWait(Barrier* _barrier, actionFunc _actionFunc, void* _context)
{
	unsigned int myBatch, myId = 0;
	
	if(!_barrier)
	{
		return FAIL;
	}
	
	if(_barrier->m_shutDownflag == SHUT_DOWN)
	{
		return SHUT_DOWN;
	}
	
	pthread_mutex_lock(&_barrier->m_mutex);
	
 	++_barrier->m_counter;
	myId = SetID(_barrier);
	myBatch = SetBatch(_barrier);
 		
	while(myId != 0 && GATE_CLOSE == _barrier->m_firstGateMode)
	{
	 	while(myBatch ==_barrier->m_curBatch)
	 	{
		 	WaitOnFirstGate(_barrier);		
	 	} 
	}
	
	if(myId == 0)
	{
	 	OpenFirstGate(_barrier);	
	}
	
	++_barrier->m_waitingRoomCounter;
	
	while(_barrier->m_waitingRoomCounter != _barrier->m_capacity && GATE_CLOSE == _barrier->m_secondGateMode)
	{
	 	WaitOnSecondGate(_barrier, _actionFunc, _context);
	}
	 	
	if( _barrier->m_waitingRoomCounter == _barrier->m_capacity)
	{
	 	OpenSecondGate(_barrier, _actionFunc, _context);		
	}	
	 			
	pthread_mutex_unlock(&_barrier->m_mutex);
	
	return _barrier->m_shutDownflag == SHUT_DOWN ? 1 : 0;
}

/****************************************************************/
static void WaitOnFirstGate(Barrier* _barrier)
{
	pthread_cond_wait(&_barrier->m_waitingRoomVar, &_barrier->m_mutex);	
	return;
}

static void OpenFirstGate(Barrier* _barrier)
{
	++_barrier->m_curBatch;
    _barrier->m_secondGateMode = GATE_CLOSE;
	_barrier->m_firstGateMode = GATE_OPEN; 
	pthread_cond_broadcast(&_barrier->m_waitingRoomVar);
	return;
}

static void WaitOnSecondGate(Barrier* _barrier, actionFunc _actionFunc, void* _context)
{
	
	if(_actionFunc)
	{
		 _actionFunc(_context);	
	}
	pthread_cond_wait(&_barrier->m_insideCondVar, &_barrier->m_mutex);

	return;
}

static void OpenSecondGate(Barrier* _barrier, actionFunc _actionFunc, void* _context)
{

	if(_actionFunc)
	{
		_actionFunc(_context);	
	}
	
	_barrier->m_waitingRoomCounter = EMPTY;	
	_barrier->m_firstGateMode = GATE_CLOSE; 
    _barrier->m_secondGateMode =  GATE_OPEN;		
	pthread_cond_broadcast(&_barrier->m_insideCondVar);
	
	return;
}		

static unsigned int SetID(Barrier* _barrier)
{
	
	unsigned int id = _barrier->m_counter % _barrier->m_capacity;
	
	if(id == 0)
 	{
 		++_barrier->m_numOfBatches;
 	}
	
	return id;
}

static unsigned int SetBatch(Barrier* _barrier)
{
	return  _barrier->m_counter / _barrier->m_capacity;
}

	
