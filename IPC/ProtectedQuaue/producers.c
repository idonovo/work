#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>     
 
#include "producers.h"
#include "queue.h"

#define SUCCESS 0
#define EMPTY 0

struct Producers
{
	pthread_t* m_producersThreads;
	size_t m_numOfCycls;
	size_t m_numOfProducers;
};

struct ProducersContext
{
	Queue* m_questionsQueue;
	Queue* m_answersQueue;
	size_t m_numOfCycls;
};


static void* ProducerRoutine(void* _context);
/**********************************************************************************/
Producers* CreateProducers(size_t _numOfProducers, size_t _numOfCycels)
{

	Producers* producers;
	
	producers= malloc(_numOfProducers * sizeof(Producers));
	if(!producers)
	{
		return NULL;
	}
	
	producers->m_producersThreads= malloc(_numOfProducers * sizeof(pthread_t));
	if(!producers->m_producersThreads)
	{
		return NULL;
	}
	
	producers->m_numOfCycls = _numOfCycels;
	producers->m_numOfProducers = _numOfProducers;
	return producers;
}

int ExecuteProducerThreads(Producers* _producers, void* _context)
{
	size_t i;
	int status;
	
	for(i = 0; i <_producers->m_numOfProducers; ++i)
	{
		pthread_create(&_producers->m_producersThreads[i], NULL,  ProducerRoutine, _context);

	}
	return 0;
}

void* CreateProducerContext(Queue* _questionsQueue, Queue* _answersQueue, size_t _numOfCycels)
{
	ProducersContext* producersContext;
	
	producersContext = malloc(sizeof(ProducersContext));
	if(!producersContext)
	{
		return NULL;
	}
	
	producersContext->m_questionsQueue = _questionsQueue;
	producersContext->m_answersQueue = _answersQueue;
	producersContext->m_numOfCycls = _numOfCycels;
	
	return (void*)producersContext;
}
 
static void* ProducerRoutine(void* _context)
{
	size_t i;
	pid_t pid;
	char* question = "what is your name?";
	char* answer = NULL;
	pid =pthread_self();
	
	for(i = 0; i < ((ProducersContext*)_context)->m_numOfCycls; ++i)
	{
		QueueInsert(((ProducersContext*)_context)->m_questionsQueue, (void*)question);
		while(EMPTY == NumOfItems(((ProducersContext*)_context)->m_answersQueue))
		{
			pthread_cond_wait(&((ProducersContext*)_context)->m_answersQueuecond->m_fullCond), 
					&((ProducersContext*)_context)->m_answersQueuecond->m_mutex);
		}	
		QueueRemove(((ProducersContext*)_context)->m_answersQueue, (void**)&answer);
		printf("thread id %d got answer ", (int)pid);
	}
	return; 
}

void ProducersJoin(const Producers* _producers)
{
	size_t i;
	
	for(i = 0; i < _producers->m_numOfProducers; ++i)
	{
		pthread_join(_producers->m_producersThreads[i],NULL);
	}
	return;
}

DestroyProducersData(Producers* _producers, void* _context);
{

	free(_producers->m_producersThreads);
	free(_producers);
	free((ProducersContext*)_context);
	
	return;	
}
