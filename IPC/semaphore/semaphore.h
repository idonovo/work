#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */

#define BUFFER_SIZE  32

typedef struct Input
{
	int m_create;
	int m_destroy;
	int m_howToStop;
	int m_nCycels;
	int m_verb;
	int m_speed;
	int m_pings;
	char m_file[BUFFER_SIZE];
	char m_binSem[BUFFER_SIZE];
	char m_countSem[BUFFER_SIZE];
	
}Input;


/*************************************************************************/
/*TODO extand documantation. to parse and analaise flags inputs from user. the function setes her on defalts if there is no input from user */ 
void ParseInput(Input* _input, int argc, char **argv);

/* a function to manage reader side in multipule writeres mQueue */
int BePong(Input* _input);

/* a function to manage writers side in multipule writeres mQueue */
int BePing(Input* _input);

#endif

