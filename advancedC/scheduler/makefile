CFLAGS = -g -ansi -pedantic -Wall -Wconversion -std=gnu99 
INC_PATH = ../../inc/
LIB_PATH = ../../libs/
CC = gcc

a.out:  tests.c $(LIB_PATH)libperiodic.so.1.0 mytime.h tasks.h 
	gcc $(CFLAGS) tests.c $(LIB_PATH)libperiodic.so.1.0 

$(LIB_PATH)libperiodic.so.1.0: time.o tasks.o periodic.o heap.o genVec.o
	gcc -shared -Wl,-soname,libperiodic.so.1 -o libperiodic.so.1.0 time.o tasks.o periodic.o heap.o genVec.o 
	ln -sf libperiodic.so.1.0 $(LIB_PATH)libperiodic.so.1
	ln -sf libperiodic.so.1.0 $(LIB_PATH)libperiodic.so
	mv libperiodic.so.1.0 $(LIB_PATH)
	
time.o: time.c mytime.h
	$(CC) $(CFLAGS) time.c -fPIC -c
	
tasks.o: tasks.c tasks.h
	$(CC) $(CFLAGS) tasks.c -fPIC -c
	
periodic.o: periodic.c $(INC_PATH)preiodic.h
	$(CC) $(CFLAGS) periodic.c -fPIC -c
	
heap.o: 
	make -C ../Heap
	
clean:
	rm  -f time.o tasks.o periodic.o $(LIB_PATH)libperiodic.so.1.0 $(LIB_PATH)libperiodic.so.1  $(LIB_PATH)libperiodic.so a.out
			
run:
	export LD_LIBRARY_PATH=../../libs/:$LD_LIBRARY_PATH 


