
FLAGS = -ansi -pedantic -Wall -g -std=gnu99
LIB_PATH = ../../libs/

ping.out: ping.c  $(LIB_PATH)libmulti.so.1.0
	gcc  $(FLAGS)  ping.c  $(LIB_PATH)libmulti.so.1.0 -o ping.out
	
pong.out: pong.c  $(LIB_PATH)libmulti.so.1.0 
	gcc  $(FLAGS) pong.c  $(LIB_PATH)libmulti.so.1.0 -o pong.out
	
$(LIB_PATH)libmulti.so.1.0  :  multi.o
	gcc -shared -Wl,-soname,libmulti.so.1 -o libmulti.so.1.0 multi.o
	ln -sf libmulti.so.1.0 $(LIB_PATH)libmulti.so.1
	ln -sf libmulti.so.1.0 $(LIB_PATH)libmulti.so
	mv libmulti.so.1.0 $(LIB_PATH)
	
multi.o:  multi.c multi.h
	gcc -c -$(FLAGS) multi.c -fPIC

clean:
	rm multi.o $(LIB_PATH)libmulti.so.1.0 $(LIB_PATH)libmulti.so.1 $(LIB_PATH)libmulti.so ping.out pong.out
	
run:
	export LD_LIBRARY_PATH=../../libs/:$LD_LIBRARY_PATH 
	


