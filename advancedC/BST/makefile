
FLAGS = -ansi -pedantic -Wall -g
LIB_PATH = ../../libs/

a.out:   tests.c  $(LIB_PATH)libBST.so.1.0
	gcc  $(FLAGS)  tests.c  $(LIB_PATH)libBST.so.1.0
	
$(LIB_PATH)libBST.so.1.0: Binary.o
	gcc -shared -Wl,-soname,libBST.so.1 -o libBST.so.1.0 Binary.o
	ln -sf libBST.so.1.0 $(LIB_PATH)libBST.so.1
	ln -sf libBST.so.1.0 $(LIB_PATH)libBST.so
	mv libBST.so.1.0 $(LIB_PATH)
	
	
double.o: Binary.c ../../inc/bin_tree.h
	gcc -c -$(FLAGS) -fPIC *.c
	

clean:
	rm double.o $(LIB_PATH)libBST.so.1.0 $(LIB_PATH)libBST.so.1 $(LIB_PATH)libBST.so a.out
	
run:
	export LD_LIBRARY_PATH=../../libs/:$LD_LIBRARY_PATH 
