#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>    
 
#include "producers.h"
#include "queue.h"

#define EMPTY 0
#define DEFAULT_SIZE 5

int g_num = 0;

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

/***********************************************************************************/
static void* ProducerRoutine(void* _context);
/**********************************************************************************/
void ParseInput(Input* _input, int argc, char **argv)
{
	int c;

	_input->m_numOfCycls =  DEFAULT_SIZE;
	_input->m_numOfProducers =  DEFAULT_SIZE;
	_input->m_numOfConsumers =  DEFAULT_SIZE;
	_input->m_queueSize =  DEFAULT_SIZE;
	
	while ((c = getopt (argc, argv, "o: p: c: s:")) != -1)
	{
		switch (c)
		{
		case 'o':
			_input->m_numOfCycls = atoi(optarg);
			break;
		case 'p':
			_input->m_numOfProducers = atoi(optarg);
			break;
		case 'c':
			_input->m_numOfConsumers = atoi(optarg);
			break;
		case 's':
			_input->m_queueSize = atoi(optarg);
			break;
		case '?':
			fprintf (stderr, "\n invalid argument inserted \n");
			continue;
		}
	}
	fprintf (stderr,"Usage: [o:] %u  [p:]  %u [c:]  %u [s:]  %u  \n", _input->m_numOfCycls, _input->m_numOfProducers, _input->m_numOfConsumers, _input->m_queueSize);
	return ;
}

Producers* CreateProducers(size_t _numOfProducers, size_t _numOfCycls)
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
	
	producers->m_numOfCycls = _numOfCycls;
	producers->m_numOfProducers = _numOfProducers;
	return producers;
}

int ExecuteProducerThreads(Producers* _producers, void* _context)
{
	size_t i;
	
	for(i = 0; i <_producers->m_numOfProducers; ++i)
	{
		pthread_create(&_producers->m_producersThreads[i], NULL,  ProducerRoutine, _context);

	}
	return 0;
}

void* CreateProducerContext(Queue* _questionsQueue, Queue* _answersQueue, size_t _numOfCycls)
{
	ProducersContext* producersContext;
	
	producersContext = malloc(sizeof(ProducersContext));
	if(!producersContext)
	{
		return NULL;
	}
	
	producersContext->m_questionsQueue = _questionsQueue;
	producersContext->m_answersQueue = _answersQueue;
	producersContext->m_numOfCycls = _numOfCycls;
	
	return (void*)producersContext;
}
 
static void* ProducerRoutine(void* _context)
{
	size_t i;
	pid_t pid;
	char* question = "what is your name?\n";
	char* answer = NULL;
	pid = pthread_self();
	
	for(i = 0; i < ((ProducersContext*)_context)->m_numOfCycls; ++i)
	{
		printf("thread id %u sends a question num: %d\n", pid, ++g_num);
		QueueInsert(((ProducersContext*)_context)->m_questionsQueue, (void*)question);
		QueueRemove(((ProducersContext*)_context)->m_answersQueue, (void**)&answer);
		printf("thread id %u got answer\n", pid);
	}
	return _context; 
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

void DestroyProducersData(Producers* _producers, void* _context)
{

	free(_producers->m_producersThreads);
	free(_producers);
	free((ProducersContext*)_context);
	
	return;	
}
