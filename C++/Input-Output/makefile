# Global definitions
CC = g++

#SFLAGS = -g -shared -Wl,-soname,
CXXFLAGS = -g -Wall -ansi -pedantic -std=gnu++11
LDFLAGS = -g

# Directory structure
INC_DIR = ../../inc/
CXXFLAGS += -I$(INC_DIR)

#LIB_DIR = ../../../lib
#LDFLAGS += -L$(LIB_DIR)
#LIB_NAME = libfeeder.so
#LDLIBS =-lPHash -lLinkedList

# all contents of current directory
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

# Target and sources
TARGET = main
#LIB_SRCS = ../communication/comm.c
#LIB_OBJS = $(LIB_SRCS:.c=.o)

# Dependencies
all: $(TARGET)

$(TARGET): $(OBJS) $(LIB_OBJS)

include depends

depends:
	$(CC) -MM -I$(INC_DIR) $(OBJS:.o=.cpp) > depends
	
#commit: $(LIB_FILE).1.0
#$(LIB_FILE): $(LIB_OBJS)
#   $(CC) $(SFLAGS)$(LIB_NAME).1 -o $(LIB_NAME).1.0 $(LIB_OBJS)
#   ln -sf $(LIB_NAME).1.0 $(LIB_FILE).1
#   ln -sf $(LIB_NAME).1.0 $(LIB_FILE)
#   mv $(LIB_NAME).1.0 $(LIB_DIR)/

clean:
	-rm -f *.o
	-rm -f test
	-rm -f depends
	
#   -rm -f $(LIB_FILE) $(LIB_FILE).1 $(LIB_FILE).1.0

run: all
	./main
	cat textAscii.txt
	
gdb: all
	gdb ./main


