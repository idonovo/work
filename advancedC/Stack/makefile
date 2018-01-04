
FLAGS = -ansi -pedantic -Wall -g

INC_PATH = ../../inc/
LIB_PATH = ../../libs/

a.out:  Double_Iter testStack.c  $(LIB_PATH)libstack.a  $(LIB_PATH)liblist.a 
	gcc  $(FLAGS) testStack.c $(LIB_PATH)libstack.a  $(LIB_PATH)liblist.a
	
$(LIB_PATH)libstack.a:  stack.o
	ar -cvq libstack.a  stack.o
	mv libstack.a $(LIB_PATH)
	
stack.o:  stack.c $(INC_PATH)stack.h
	gcc -c -$(FLAGS) stack.c 

 Double_Iter: 
	make -C ../Double_Iter


clean:
	rm stack.o $(LIB_PATH)libstack.a a.out
	make -C ../Double_Iter clean
