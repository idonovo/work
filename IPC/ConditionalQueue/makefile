
FLAGS = -ansi -pedantic -Wall -g -std=gnu99 -pthread -lrt
LIB_PATH = ../../libs/
OBJECTS= queue.o consumer.o producers.o	

all: procQ

procQ: main.c  $(OBJECTS)
	gcc  $(FLAGS) main.c  $(OBJECTS) -o procQ

queue.o: queue.c queue.h
	gcc $(FLAGS) -c queue.c 
	
consumer.o: consumer.c consumer.h
	gcc $(FLAGS) -c consumer.c 
	
producers.o: producers.c producers.h
	gcc $(FLAGS) -c producers.c 
	
clean:
	rm -f procQ *.o
	


