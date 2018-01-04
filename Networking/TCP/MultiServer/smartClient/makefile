# Global definitions
CC = gcc

#SFLAGS = -g -shared -Wl,-soname,
CFLAGS = -g
LDFLAGS = -g -lm

# Directory structure
INC_DIR = ../../inc/
CFLAGS += -I$(INC_DIR)

#LIB_DIR = ../../../lib
#LDFLAGS += -L$(LIB_DIR)
#LIB_NAME = libfeeder.so
#LDLIBS =-lPHash -lLinkedList

# all contents of current directory
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# Target and sources
TARGET = main
PARA = 2002 192.168.0.7
#LIB_SRCS = ../communication/comm.c
#LIB_OBJS = $(LIB_SRCS:.c=.o)

# Dependencies
all: $(TARGET)

$(TARGET): $(OBJS) $(LIB_OBJS)
#	$(CC) $(TARGET_ARCH) $(GCCFLAGS) $^ $(LDLIBS) $(LDFLAGS) -o $@

include depends

depends:
	$(CC) -MM -I$(INC_DIR) $(OBJS:.o=.c) > depends
	
#commit: $(LIB_FILE).1.0
#$(LIB_FILE): $(LIB_OBJS)
#   $(CC) $(SFLAGS)$(LIB_NAME).1 -o $(LIB_NAME).1.0 $(LIB_OBJS)
#   ln -sf $(LIB_NAME).1.0 $(LIB_FILE).1
#   ln -sf $(LIB_NAME).1.0 $(LIB_FILE)
#   mv $(LIB_NAME).1.0 $(LIB_DIR)/

clean:
	-rm -f *.o
	-rm -f $(TARGET)
	-rm -f depends
	
#   -rm -f $(LIB_FILE) $(LIB_FILE).1 $(LIB_FILE).1.0

run: all
	strace ./$(TARGET) $(PARA)

gdb: all
	gdb  --args ./$(TARGET) $(PARA)




