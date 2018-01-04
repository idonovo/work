

CFLAGS = -ansi -pedantic -Wall -Wconversion -std=gnu99 -m32 -pthread -g
CC = gcc
INC_PATH = ../../inc/queue.o
QUEUE_PATH = ../../IPC/ProtectedQuaue/
LIBS =  ../logger/log.o  ../logger/config.o transmissionData.o ParseAndPush.o  fidders.o tests.o  

all: feeder

feeder:  $(LIBS) 
	$(CC) $(CFLAGS) $(LIBS) -o feeder
	
transmissionData.o:
	$(CC) $(CFLAGS) transmissionData.c -c
	
ParseAndPush.o: 
	$(CC) $(CFLAGS) ParseAndPush.c -c

fidders.o: fidders.c
	$(CC) $(CFLAGS) fidders.c -c 

tests.o: tests.c
	$(CC) $(CFLAGS) tests.c -c 

	
clean:
	rm -f proccessor *.o logger.txt 
	
run: all
	./feeder
	
gdb: all
	gdb ./feeder
