CFLAGS = -g -ansi -pedantic -Wall -Wconversion -std=gnu99 -m32 -pthread
CC = gcc
INC_PATH = ../../inc/
HASH_PATH = ../../IPC/ProtectedHash/
LIB_PATH = ../../libs/
OBJS =  storeSubData.o storeOptData.o tests.o proccessorManagment.o $(HASH_PATH)hashmap.o $(LIB_PATH)liblist.so  ../logger/log.o  ../logger/config.o transmissionData.o dealQuery.o  

all: proccessor

proccessor:  $(OBJS) 
	$(CC) $(OBJS) -o proccessor -pthread
	
storeSubData.o:
	$(CC) $(CFLAGS) storeSubData.c -c

storeOptData.o:
	$(CC) $(CFLAGS) storeOptData.c -c
	
transmissionData.o:
	$(CC) $(CFLAGS) transmissionData.c -c
	
dealQuery.o: 
	$(CC) $(CFLAGS) dealQuery.c -c

proccessorManagment.o:
	$(CC) $(CFLAGS) proccessorManagment.c -c
	
tests.o: tests.c
	$(CC) $(CFLAGS) tests.c -c
	
clean:
	rm -f proccessor *.o logger.txt
	
run: all
	./proccessor
	
gdb: all
	gdb ./proccessor
