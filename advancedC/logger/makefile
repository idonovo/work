
FLAGS = -ansi -pedantic -Wall -g

INC_PATH = ../../inc/
LIB_PATH = ../../libs/

a.out: log.c  logtests.c $(LIB_PATH)liblog.a  $(LIB_PATH)libconfig.a  
	gcc  $(FLAGS) logtests.c $(LIB_PATH)liblog.a  $(LIB_PATH)libconfig.a 
	
$(LIB_PATH)liblog.a:  log.o
	ar -cvq liblog.a  log.o
	mv liblog.a $(LIB_PATH)

$(LIB_PATH)libconfig.a:  config.o
	ar -cvq libconfig.a  config.o
	mv libconfig.a $(LIB_PATH)
	
log.o:  log.c $(INC_PATH)logger.h
	gcc -c -$(FLAGS) log.c

config.o:  config.c $(INC_PATH)config.h
	gcc -c -$(FLAGS) config.c

clean:
	rm log.o $(LIB_PATH)liblog.a config.o $(LIB_PATH)libconfig.a a.out

