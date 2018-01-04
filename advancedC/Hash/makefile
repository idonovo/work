CFLAGS = -g -ansi -pedantic -Wall -Wconversion 
INC_PATH = ../../inc/
LIB_PATH = ../../libs/

a.out: Double_Iter testHash.c $(LIB_PATH)libhash.so.1.0  $(INC_PATH)HashMap.h
	gcc -g -ansi -pedantic -Wall -Wconversion  testHash.c $(LIB_PATH)libhash.so.1.0  $(LIB_PATH)liblist.so.1.0

$(LIB_PATH)libhash.so.1.0: hashmap.o
	gcc -shared -Wl,-soname,libhash.so.1 -o libhash.so.1.0 hashmap.o
	ln -sf libhash.so.1.0 $(LIB_PATH)libhash.so.1
	ln -sf libhash.so.1.0 $(LIB_PATH)libhash.so
	mv libhash.so.1.0 $(LIB_PATH)
	
Hash.o: hashmap.c $(INC_PATH)HashMap.h
	$(CC) $(CFLAGS) hashmap.c -c

Double_Iter: 
	make -C ../Double_Iter

clean:
		make -C ../Double_Iter clean
		rm Hash.o $(LIB_PATH)libhash.so.1.0 $(LIB_PATH)libhash.so.1 $(LIB_PATH)libhash.so a.out
			
run:
	export LD_LIBRARY_PATH=../../libs/:$LD_LIBRARY_PATH 


