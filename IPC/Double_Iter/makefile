
FLAGS = -ansi -pedantic -Wall -g
LIB_PATH = ../../libs/

a.out:  tests.c  $(LIB_PATH)liblist.so.1.0
	gcc  $(FLAGS) tests.c  $(LIB_PATH)liblist.so.1.0
	
 $(LIB_PATH)liblist.so.1.0: double.o
	gcc -shared -Wl,-soname,liblist.so.1 -o liblist.so.1.0 double.o
	ln -sf liblist.so.1.0 $(LIB_PATH)liblist.so.1
	ln -sf liblist.so.1.0 $(LIB_PATH)liblist.so
	mv liblist.so.1.0 $(LIB_PATH)
	
	
double.o: double.c ../../inc/double.h ../../inc/list_itr.h ../../inc/list_functions.h
	gcc -c -$(FLAGS) *.c

clean:
	rm double.o $(LIB_PATH)liblist.so.1.0 $(LIB_PATH)liblist.so.1 $(LIB_PATH)liblist.so a.out
	
run:
	export LD_LIBRARY_PATH=../../libs/:$LD_LIBRARY_PATH 
