#ifndef __MQUEUE_H__
#define __MQUEUE_H__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define BUFFER_SIZE  32
#define QUEUE_FILENAME  "/home/student/Desktop/work/IPC/mQueues"
#define MSG_STOP    "exit"
#define QUEUE_ID   'a'
#define FAIL -1
#define SUCCESS 0

typedef struct MessageBox{
    long m_type;     
    int m_pid;
    char m_text[BUFFER_SIZE];   
}MessageBox;


typedef struct Input
{
	int m_create;
	int m_destroy;
	int m_howToStop;
	int m_nCycels;
	int m_verb;
	size_t m_speed;
	char m_file[32];
	
}Input;

/*************************************************************************/
void ParseInput(Input* _input, int argc, char **argv);

void InsertToBuffer(char* _readbuffer, char _x, int _size);

void InitMessageBox(MessageBox* _messageBox, char* _buffer, int _pid);

int CreateQueue(int _key, int _flag);

int IsLastMessage(MessageBox* _messageBox);

int SendEOF(MessageBox* _messageBox, int _howToStop, int _msqid);

#endif

