
FLAGS = -ansi -pedantic -Wall -g
LIB_PATH = ../../libs/

a.out: tests.c  $(LIB_PATH)libvec.so.1.0
	gcc  $(FLAGS) tests.c $(LIB_PATH)libvec.so.1.0
	
$(LIB_PATH)libvec.so.1.0 : genVec.o
	
	gcc -shared -Wl,-soname,libvec.so.1 -o libvec.so.1.0 genVec.o
	ln -sf libvec.so.1.0 $(LIB_PATH)libvec.so.1
	ln -sf libvec.so.1.0 $(LIB_PATH)libvec.so
	mv libvec.so.1.0 $(LIB_PATH)
	
genVec.o: genVec.c ../../inc/genVec.h ../../inc/ADTDefs.h 
	gcc -c -$(FLAGS) -Wall -fPIC genVec.c -c
	
clean:
	rm genVec.o $(LIB_PATH)libvec.so.1.0 $(LIB_PATH)libvec.so.1 $(LIB_PATH)libvec.so a.out
	
run:
	export LD_LIBRARY_PATH=../../libs/:$LD_LIBRARY_PATH 
