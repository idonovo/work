
FLAGS = -ansi -pedantic -Wall -g -std=gnu99 -fPIC
LIB_PATH = ../../libs/

all: ping.out pong.out

ping.out: ping.o  $(LIB_PATH)libmulti.so
	gcc  $(FLAGS)  ping.o  $(LIB_PATH)libmulti.so -o ping.out
	
pong.out: pong.o  $(LIB_PATH)libmulti.so 
	gcc   $(FLAGS)  pong.o  $(LIB_PATH)libmulti.so -o pong.out
	
$(LIB_PATH)libmulti.so  :  multi.o
	gcc -shared -Wl,-soname,libmulti.so.1 -o libmulti.so.1.0 multi.o
	ln -sf libmulti.so.1.0 $(LIB_PATH)libmulti.so.1
	ln -sf libmulti.so.1.0 $(LIB_PATH)libmulti.so
	mv libmulti.so.1.0 $(LIB_PATH)
	
multi.o:  multi.c multi.h
	gcc -c $(FLAGS) multi.c 

ping.o: ping.c multi.h
	gcc -c $(FLAGS) ping.c
	
pong.o: pong.c multi.h
	gcc -c $(FLAGS) pong.c
	

clean:
	rm *.o $(LIB_PATH)libmulti.so.1.0 $(LIB_PATH)libmulti.so.1 $(LIB_PATH)libmulti.so *.out
	
run:
	export LD_LIBRARY_PATH=../../libs/:$LD_LIBRARY_PATH 
	


