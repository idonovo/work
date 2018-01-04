#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>    
#include <time.h> 

#define NUM_OF_THREADS 400000
  
int g_temp = 23;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* ChangTemp(void* _x)
{
	
	pthread_mutex_lock(&mutex);
	g_temp += ((rand() % 4) -2);
	printf("current temp is %d\n", g_temp);
  	pthread_cond_signal(&cond); 
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
	
}

void* Sensor(void* _x)
{
	pthread_mutex_lock(&mutex);
	
	while(g_temp <= 25 && g_temp >= 21)
	{
		pthread_cond_wait(&cond, &mutex);
	}

	g_temp = 23;
	printf("change current temp back to %d\n", g_temp);
	pthread_mutex_unlock(&mutex);
		
	pthread_exit(NULL);	 
}

int main()
{
		
	size_t i;
	pthread_t changeTempThreads[NUM_OF_THREADS];
	pthread_t sensorThreads[NUM_OF_THREADS];
	
	srand(time(NULL));
	
	for(i=0; i<NUM_OF_THREADS; i++)
	{
		pthread_create(&sensorThreads[i], NULL, Sensor, NULL);
		pthread_create(&changeTempThreads[i], NULL, ChangTemp, NULL);
	}

	for(i=0; i<NUM_OF_THREADS; i++)
	{
		pthread_join(changeTempThreads[i],NULL);
		//pthread_join(sensorThreads[i],NULL);
	}
		
	return 0;
}
