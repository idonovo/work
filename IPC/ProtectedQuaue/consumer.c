#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>           
#include <sys/stat.h>   
#include <pthread.h>   

#include "consumer.h"
#include "queue.h"

#define SHUT_DOWN "exit"
#define SUCCESS 0
#define NAME "ido"

struct Consumers
{  
	pthread_t* m_consumersThreads;
	size_t m_numOfConsumers;
};

struct ConsumersContext
{
	Queue* m_questionsQueue;
	Queue* m_answersQueue;
	Consumers* m_consumerData;
};

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

int ExecuteConsumerThreads(void* _context)
{
    size_t i;
	int status;
	
	for(i = 0; i <((ConsumersContext*)_context)->m_consumerData->m_numOfConsumers; ++i)
	{
		status = pthread_create(&((ConsumersContext*)_context)->m_consumerData->m_consumersThreads[i], NULL,  ConsumerRoutine, _context);
		
		if (SUCCESS != status)
		{
        	perror("pthread_create failed");
 			
         	return -1; 
		}
	}
	return 0;
}

void* CreateConsumersContext(Queue* _questionsQueue, Queue* _answersQueue, Consumers* _consumers)
{
    ConsumersContext* consumersContext;
	
	consumersContext = malloc(sizeof(ConsumersContext));
	if(!consumersContext)
	{
		return NULL;
	}
	
	consumersContext->m_questionsQueue = _questionsQueue;
	consumersContext->m_answersQueue = _answersQueue;
	consumersContext->m_consumerData = _consumers;
	
	return (void*)consumersContext;
}

void* ConsumerRoutine(void* _context)
{
	pid_t pid;
	char*   question;
	char* answer = NAME;
	pid =pthread_self();
	
	for(;;)
	{		
		QueueRemove(((ConsumersContext*)_context)->m_questionsQueue, (void**)&question);
		if(1)
		{
		    break;
		}
		printf("the question is %s", question);
		
		sleep(1);
			
		QueueInsert(((ConsumersContext*)_context)->m_answersQueue, (void*)answer);
		printf("the answer by thread id %d is %s", (int)pid, answer);
		
		if(0 == QueueIsEmpty(((ConsumersContext*)_context)->m_answersQueue))
		{
		    SendExitMessage(((ConsumersContext*)_context));
		}
	}
	
	pthread_exit(NULL);
}

int ConsumersJoin(const Consumers* _consumers, void* _context)
{
    size_t i;
	int status;
	
	for(i = 0; i < _consumers->m_numOfConsumers; ++i)
	{
		status = pthread_join(_consumers->m_consumersThreads[i],NULL);
        	
        	if (SUCCESS != status)
        	{
		    	perror("sem_wait failed");
		     	return -1; 
        	}
	}
	
	return 1;
}

void DestroyConsumerContext(void* _context)
{

	QueueDestroy(((ConsumersContext*)_context)->m_questionsQueue);
	QueueDestroy(((ConsumersContext*)_context)->m_answersQueue);
	free(((ConsumersContext*)_context)->m_consumerData->m_consumersThreads);
	free(((ConsumersContext*)_context)->m_consumerData);
	
	return;	
}

void SendExitMessage(ConsumersContext* _context)
{
    size_t i;
    char* exitMessage = SHUT_DOWN;
    
    for(i = 0; i < _context->m_consumerData->m_numOfConsumers; ++i)
	{
		QueueInsert(_context->m_questionsQueue, (void*)exitMessage);
	}
	return;
}

