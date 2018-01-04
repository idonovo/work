#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>  
#include <unistd.h>      

#include "consumer.h"
#include "queue.h"

#define SHUT_DOWN "exit"
#define NAME "ido"
#define EMPTY 0

struct Consumers
{  
	pthread_t* m_consumersThreads;
	size_t m_numOfConsumers;
};

struct ConsumersContext
{
	Queue* m_questionsQueue;
	Queue* m_answersQueue;
	size_t m_numOfCycls;
};

/***************************************************************/
static void* ConsumerRoutine(void* _context);
/***********************************************************/
Consumers* CreateConsumers(size_t _numOfConsumers)
{
    Consumers* consumers;
	
	consumers= malloc(_numOfConsumers * sizeof(Consumers));
	if(!consumers)
	{
		return NULL;
	}
	
	consumers->m_consumersThreads= malloc(_numOfConsumers * sizeof(pthread_t));
	if(!consumers->m_consumersThreads)
	{
		return NULL;
	}
	
	consumers->m_numOfConsumers = _numOfConsumers;
	return consumers;
}

int ExecuteConsumerThreads(Consumers* _consumers, void* _context)
{
    size_t i;
	
	for(i = 0; i <_consumers->m_numOfConsumers; ++i)
	{
		pthread_create(&_consumers->m_consumersThreads[i], NULL,  ConsumerRoutine, _context);
		 
	}
	return 0;
}

void* CreateConsumersContext(Queue* _questionsQueue, Queue* _answersQueue)
{
    ConsumersContext* consumersContext;
	
	consumersContext = malloc(sizeof(ConsumersContext));
	if(!consumersContext)
	{
		return NULL;
	}
	
	consumersContext->m_questionsQueue = _questionsQueue;
	consumersContext->m_answersQueue = _answersQueue;
	
	return (void*)consumersContext;
}

static void* ConsumerRoutine(void* _context)
{
	pid_t pid;
	char* question;
	char* answer = NAME;
	pid =pthread_self();
	
	for(;;)
	{		
		QueueRemove(((ConsumersContext*)_context)->m_questionsQueue, (void**)&question);
		printf("theard id %u got question:  %s\n", pid, question);
		sleep(1);	
		QueueInsert(((ConsumersContext*)_context)->m_answersQueue, (void*)answer);
		printf("theard id %u responded\n", pid);
		
		if(EMPTY == NumOfItems(((ConsumersContext*)_context)->m_answersQueue) && EMPTY == NumOfItems(((ConsumersContext*)_context)->m_questionsQueue))
		{
		    break;
		}
	}
	
	return NULL;
}

int ConsumersJoin(const Consumers* _consumers)
{
    size_t i;

	for(i = 0; i < _consumers->m_numOfConsumers; ++i)
	{
		pthread_join(_consumers->m_consumersThreads[i],NULL);
	}
	
	return 1;
}


void DestroyConsumerContextData(Consumers* _consumers, void* _context)
{

	free(_consumers->m_consumersThreads);
	free(_consumers);
	free((ConsumersContext*)_context);
	
	return;	
}


