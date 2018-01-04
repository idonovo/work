
FLAGS = -ansi -pedantic -Wall -g
LIB_PATH = ../../libs/

a.out:  vector tests.c  $(LIB_PATH)libheap.so.1.0 $(LIB_PATH)libvec.so.1.0
	gcc  $(FLAGS) tests.c $(LIB_PATH)libheap.so.1.0 $(LIB_PATH)libvec.so.1.0
	
$(LIB_PATH)libheap.so.1.0 :  heap.o
	gcc -shared -Wl,-soname,libheap.so.1 -o libheap.so.1.0 heap.o
	ln -sf libheap.so.1.0 $(LIB_PATH)libheap.so.1
	ln -sf libheap.so.1.0 $(LIB_PATH)libheap.so
	mv libheap.so.1.0 $(LIB_PATH)
	
heap.o:  heap.c ../../inc/Heap.h
	gcc -c -$(FLAGS) heap.c -fPIC
	
vector: 
	make -C ../Vector

clean:
	rm heap.o $(LIB_PATH)libheap.so.1.0 $(LIB_PATH)libheap.so.1 $(LIB_PATH)libheap.so a.out
	make -C ../Vector clean
	
run:
	export LD_LIBRARY_PATH=../../libs/:$LD_LIBRARY_PATH 
	


