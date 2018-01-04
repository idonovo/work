#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define NUM_OF_THREADS 10
 
int g_global = 11;

void* PrintInLopp(void* _tid){
	
	long local;
	int i = 0;
	long tid;
	tid = (long)_tid;
	local = g_global - tid;
	while(i < 100000)
	{
		++g_global;
		printf("thread %ld  global: %d local: %ld\n", tid, g_global, local);
		i++;
	}
	printf("\n");
	pthread_exit(NULL);
	
}

int main(){
		
	size_t i;
	int status;
	pthread_t threads[NUM_OF_THREADS];
	pthread_attr_t attr;
	
	for(i=0; i<NUM_OF_THREADS; i++){
		status = pthread_create(&threads[i], NULL, PrintInLopp,(void*)i);
		 if (status){
          printf("ERROR; return code from pthread_create() is %d\n", status);
          exit(-1);
          
       }
	}
	
	for(i=0; i<NUM_OF_THREADS; i++){
		pthread_join(threads[i],NULL);
	}
	
	pthread_exit(NULL);
}
