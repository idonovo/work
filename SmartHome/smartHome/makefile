# Global definitions
CC = g++

#SFLAGS = -g -shared -Wl,-soname,
CXXFLAGS = -g -Wall -ansi -pedantic 
LDFLAGS = -g -pthread -ldl 

# Directory structure
INC_DIR = ./SO/
CXXFLAGS += -I$(INC_DIR)

#LIB_DIR = ../../../lib
#LDFLAGS += -L$(LIB_DIR)
#LIB_NAME = libfeeder.so
#LDLIBS =-lPHash -lLinkedList

# all contents of current directory
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

# Target and sources
TARGET = tests
#LIB_SRCS = AgentCreator.cpp
LIB_OBJS = $(LIB_SRCS:.cpp=.o)

# Dependencies
all: $(TARGET) subs

$(TARGET): $(OBJS) $(LIB_OBJS)
	$(CC) $(TARGET_ARCH) $(LOADLIBES) $^ $(LDLIBS) $(LDFLAGS) -o $@

include depends

depends:
	$(CC) -MM -I$(INC_DIR) $(OBJS:.o=.cpp) > depends
	
subs:
	make -C ../SO/FireSystem 
	make -C ../SO/TempControlSystem
	
commit: $(LIB_FILE)
$(LIB_FILE): $(LIB_OBJS)
	$(CC) $(SFLAGS)$(LIB_NAME).1 -o $(LIB_NAME).1.0 $(LIB_OBJS)
#   ln -sf $(LIB_NAME).1.0 $(LIB_FILE).1
#   ln -sf $(LIB_NAME).1.0 $(LIB_FILE)
#   mv $(LIB_NAME).1.0 $(LIB_DIR)/

clean:
	-rm -f $(OBJS)
	-rm -f test
	-rm -f depends
	make clean -C ../SO/FireSystem
	make clean -C ../SO/TempControlSystem
	-rm -f ./Loggers/*.txt
	mkdir ./Loggers
	
#   -rm -f $(LIB_FILE) $(LIB_FILE).1 $(LIB_FILE).1.0

run: all
	./tests
	
gdb: all
	gdb ./tests


