
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* PrintInLoop(void* _tid){
	
	int i = 1;
	long tid;
	tid = (long)_tid;
	
	printf("tid: %ld : %p\n", tid, (void*)&i);
	printf("\n");
	pthread_exit(NULL);
	
}

int main(){

	size_t i=0;
	int status;
	pthread_t threads[1000];

	
	while(1){
		status = pthread_create(&threads[i], NULL, PrintInLoop,(void*)i);
		
		 if (status){
          printf("ERROR; return code from pthread_create() is %d\n", status);
          break;      
       }
       i++;
	}
	printf("%d\n\n", i);
	
	pthread_exit(NULL);
}


	
