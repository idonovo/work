#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_OF_THREADS 2

sem_t sem_name;
int g_global = 11;

void* Increase(void* _tid){

	int i=0;

	sem_wait(&sem_name);
	
	
	while(i < 10000)
	{
		++g_global;
		printf(" global: %d\n", g_global);
		i++;
	}
	printf("\n");
	sem_post(&sem_name); 
	pthread_exit(NULL);
	
}

void* Decrease(void* _tid){
	
	int i=0;

	sem_wait (&sem_name);
	

	while(i < 10000)
	{
		--g_global;
		printf("global: %d \n", g_global);
		i++;
	}
	printf("\n");
	
	sem_post(&sem_name); 
	pthread_exit(NULL);
	
}

int main(){
	
	pthread_t consumerThread;
	pthread_t producerThread;
	
	sem_init(&sem_name, 0, 1);
	
	if(pthread_create(&producerThread, NULL, Increase,NULL))
    {
        printf("\n ERROR creating thread");
        exit(1);
    }

    if(pthread_create(&consumerThread, NULL, Decrease, NULL))
    {
        printf("\n ERROR creating thread");
        exit(1);
    }
	

	pthread_join(consumerThread, NULL);
	pthread_join(producerThread, NULL);
	
	sem_destroy(&sem_name);
	
	pthread_exit(NULL);
}
