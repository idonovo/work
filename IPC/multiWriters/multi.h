#ifndef __MULTI_H__
#define __MULTI_H__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define BUFFER_SIZE  32

typedef struct Input
{
	int m_create;
	int m_destroy;
	int m_howToStop;
	int m_nCycels;
	int m_verb;
	size_t m_speed;
	char m_file[BUFFER_SIZE];
	
}Input;


/*************************************************************************/
/*TODO extand documantation. to parse and analaise flags inputs from user. the function setes her on defalts if there is no input from user */ 
void ParseInput(Input* _input, int argc, char **argv);

/* a function to manage reader side in multipule writeres mQueue */
int BePong(Input* _input);

/* a function to manage writers side in multipule writeres mQueue */
int BePing(Input* _input);

#endif

