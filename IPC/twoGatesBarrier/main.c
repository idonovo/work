
#include <stdlib.h>
#include <pthread.h>  
#include <stdio.h> 
#include <unistd.h>  
#include <time.h>     
#include "mybarrier.h"

#define DEFAULT_SIZE 5

typedef struct Input
{
	size_t m_numOfIncrements, m_numOfCycls, m_numOfCounters;
} Input;

typedef struct CounterData
{
	int*				m_array;
	size_t				m_numOfCycls;
	size_t				m_numOfIncrements;
	Barrier*			m_barrier;
}CounterData;

typedef struct SummarizerData
{
	int*				m_array;
	int					m_sum;
	size_t				m_size;
	Barrier*			m_barrier;
}SummarizerData;
/************************************/
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;
/*************************************************/
int Sammerizing(void* _context)
{
	size_t i;
	((SummarizerData*)_context)->m_sum = 0;
	for(i = 0; i < ((SummarizerData*)_context)->m_size; ++i)
	{
		((SummarizerData*)_context)->m_sum += ((SummarizerData*)_context)->m_array[i];
		usleep((rand() %100) * 1000);
	}
	printf("the sum is: %d\n", ((SummarizerData*)_context)->m_sum);
	
	return 0;
}


int GetID()
{
	static int i = -1;
	pthread_mutex_lock(&g_mutex);
	++i;
	pthread_mutex_unlock(&g_mutex);
	return i;
}

void* Summarizer(void* _context)
{
	BarrierWait(((SummarizerData*)_context)->m_barrier, Sammerizing, _context);
	pthread_exit(NULL);
}

void* Counter(void* _context)
{
	size_t i, j;
	
	int index = GetID();
	
	for(i = 0; i <((CounterData*)_context)->m_numOfCycls; ++i)
	{
		((CounterData*)_context)->m_array[index] = (int)i;
		
		for(j = 0; j < ((CounterData*)_context)->m_numOfIncrements; ++j)
		{
			++((CounterData*)_context)->m_array[index];
			usleep((rand() %100) * 1000);
		}
		printf("the sum in thread %u is: %d\n", (size_t)pthread_self(), ((CounterData*)_context)->m_array[index]);
		BarrierWait(((CounterData*)_context)->m_barrier, NULL, NULL);
	}
	pthread_exit(NULL);
}

void SetProcessParameters(Input* _input, int argc, char **argv)
{
	int c;

	_input-> m_numOfIncrements =  DEFAULT_SIZE;
	_input-> m_numOfCycls =  DEFAULT_SIZE;
	_input-> m_numOfCounters =  DEFAULT_SIZE;
	
	while ((c = getopt (argc, argv, "i: c: t: ")) != -1)
	{
		switch (c)
		{
		case 'i':
			_input-> m_numOfIncrements = (size_t)atoi(optarg);
			break;
		case 'c':
			_input-> m_numOfCycls = (size_t)atoi(optarg);
			break;
		case 't':
			_input-> m_numOfCounters = (size_t)atoi(optarg);
			break;
		case '?':
			fprintf (stderr, "\n invalid argument inserted \n");
			continue;
		}
	}
	fprintf (stderr,"Usage: [i:] %u  [c:]  %u [t:]  %u  \n", _input-> m_numOfIncrements, _input-> m_numOfCycls, _input-> m_numOfCounters);
	return;
}

/*************************************************/

int main (int argc, char **argv)
{
	size_t i;
	pthread_t threads[DEFAULT_SIZE+DEFAULT_SIZE];
	Barrier* barrier;
	Input input;
	CounterData* counterData;
	SummarizerData* summarizerData;
	int* sum, *array;
	
	srand(time(NULL));
	
	SetProcessParameters(&input, argc, argv);
	
	array = malloc(input.m_numOfCounters * sizeof(int));	 
	barrier = BarrierCreate(input.m_numOfCounters+1);
	
	counterData = malloc(sizeof(CounterData));
	counterData->m_array = array;
	counterData->m_numOfCycls = input.m_numOfCycls;
	counterData->m_numOfIncrements = input.m_numOfIncrements;
	counterData->m_barrier = barrier;
	
	summarizerData = malloc(sizeof(SummarizerData));
	summarizerData->m_array = array;
	summarizerData->m_size = input.m_numOfCounters;
	summarizerData->m_barrier = barrier;
	
	for(i=0; i < input.m_numOfCounters; i++)
	{
		pthread_create(&threads[i], NULL, Counter, (void*)counterData);
	}

	for(i = 0; i < input.m_numOfCycls; i++)
	{
		pthread_create(&threads[input.m_numOfCounters+1], NULL, Summarizer, (void*)summarizerData);
		pthread_join(threads[input.m_numOfCounters+1], (void**)&sum);
		printf("in main: the sum is: %d\n", summarizerData->m_sum); 
	}
	
	BarrierDestroy(barrier);
	free(array);
	free(counterData);
	free(summarizerData);
	
	return 0;

}
