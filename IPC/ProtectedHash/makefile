CFLAGS = -g -ansi -pedantic -Wall -Wconversion -pthread
INC_PATH = ../../inc/
LIB_PATH = ../../libs/

all: Double_Iter run

run: testHash.c $(LIB_PATH)libhash.so.1.0 
	gcc $(CFLAGS) testHash.c $(LIB_PATH)libhash.so.1.0  $(LIB_PATH)liblist.so.1.0 -o run

$(LIB_PATH)libhash.so.1.0: hashmap.o
	gcc -shared -Wl,-soname,libhash.so.1 -o libhash.so.1.0 hashmap.o
	ln -sf libhash.so.1.0 $(LIB_PATH)libhash.so.1
	ln -sf libhash.so.1.0 $(LIB_PATH)libhash.so
	mv libhash.so.1.0 $(LIB_PATH)
	
hashmap.o: hashmap.c $(INC_PATH)HashMap.h
	$(CC) $(CFLAGS) hashmap.c -c

Double_Iter: 
	make -C ../Double_Iter

clean:
		make -C ../Double_Iter clean
		rm -f hashmap.o $(LIB_PATH)libhash.so.1.0 $(LIB_PATH)libhash.so.1 $(LIB_PATH)libhash.so run 


