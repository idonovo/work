
#include <stdlib.h>
#include <pthread.h>  
#include <stdio.h> 
#include <unistd.h>  
#include <time.h>     
#include "mybarrier.h"

#define DEFAULT_SIZE 10

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

typedef struct SummerizerData
{
	int*				m_array;
	int					m_sum;
	size_t				m_size;
	Barrier*			m_barrier;
}SummerizerData;
/************************************/
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;
/*************************************************/
int GetID()
{
	static int i = -1;
	pthread_mutex_lock(&g_mutex);
	++i;
	pthread_mutex_unlock(&g_mutex);
	return i;
}

void* Summerizer(void* _context)
{

	size_t i;
	int sum = 0;
	
	BarrierWait(((SummerizerData*)_context)->m_barrier);
	
	for(i = 0; i < ((SummerizerData*)_context)->m_size; ++i)
	{
		sum += ((SummerizerData*)_context)->m_array[i];
		usleep((rand() %100) * 1000);
	}
	printf("the sum is: %d\n", sum);
	((SummerizerData*)_context)->m_sum = sum;
	
	BarrierWait(((SummerizerData*)_context)->m_barrier);
	
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
		printf("the value in thread %u is: %d\n", (size_t)pthread_self(), ((CounterData*)_context)->m_array[index]);
		
		BarrierWait(((CounterData*)_context)->m_barrier);
		BarrierWait(((CounterData*)_context)->m_barrier);
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
	SummerizerData* summerizerData;
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
	
	summerizerData = malloc(sizeof(SummerizerData));
	summerizerData->m_array = array;
	summerizerData->m_size = input.m_numOfCounters;
	summerizerData->m_barrier = barrier;
	
	for(i=0; i < input.m_numOfCounters; i++)
	{
		pthread_create(&threads[i], NULL, Counter, (void*)counterData);
	}

	for(i = 0; i < input.m_numOfCycls; i++)
	{
		pthread_create(&threads[input.m_numOfCounters+1], NULL, Summerizer, (void*)summerizerData);
		pthread_join(threads[input.m_numOfCounters+1], (void**)&sum);
		printf("in main: the sum is: %d\n", summerizerData->m_sum); 
	}
	
	BarrierDestroy(barrier);
	free(array);
	free(counterData);
	free(summerizerData);
	
	return 0;

}
