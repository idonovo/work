#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <pthread.h>

#include "protocol.h"
#include "ParseAndPush.h"
#include "TransmissionData.h"
#include "../../inc/logger.h"
#include "../../inc/config.h"
#include "fidders.h"
#include "../../IPC/ProtectedQuaue/queue.h"


#define PATH   		"/home/student/work/CDR/Feeder"
#define REC_PATH 	"/home/student/work/CDR/CDR_FILES/"
#define WORK_PATH 	"/home/student/work/CDR/WORK_ZONE"
#define DONE_PATH 	"/home/student/work/CDR/DONE_ZONE"
#define KEY 'f'
#define TYPE 1
#define NUM_OF_THREADS 2
#define SUCCESS 0

struct FeedersContext
{
	/*Queue*				m_cdrFilesQueue; */
	ChannelData* 		m_channel;
	/*size_t 				m_numOfFeeders; */
	/*int 				m_shutDownFlag; */
	char 				m_recPath[64];
	char 				m_workPath[64];
	char 				m_donePath[64];
	char                m_curCdrFile[64];		
};

static int SetFileConfig(FeedersContext* _context, char* _configFile)
{
	/* TODO */
	return 0;
}

static int SetDefaultConfig(FeedersContext* _context)
{

	/*_context->m_cdrFilesQueue = QueueCreate(5);
	if(!_context->m_cdrFilesQueue)
	{
		return -1;
	}*/
	_context->m_channel = CreateTransmissionChannel(PATH, KEY, TYPE, NULL);
	if(!_context->m_channel)
	{
		/*QueueDestroy(_context->m_cdrFilesQueue); */
		return -1;
	}
	
	strcpy(_context->m_recPath, REC_PATH);
	strcpy(_context->m_workPath, WORK_PATH);
	strcpy(_context->m_donePath, DONE_PATH);
	strcpy(_context->m_curCdrFile, REC_PATH);
	/*_context->m_shutDownFlag = 0;
	_context->m_numOfFeeders = NUM_OF_THREADS; 
	
	if(SUCCESS != pthread_cond_init(&_context->m_condVar, NULL))
	{
		DestroyChannel(_context->m_channel);
		QueueDestroy(_context->m_cdrFilesQueue);
		return -1;
	}
	
	if(SUCCESS != pthread_mutex_init(&_context->m_mutex, NULL))
	{
		DestroyChannel(_context->m_channel);
		QueueDestroy(_context->m_cdrFilesQueue);
		pthread_cond_destroy(&_context->m_condVar);
	}*/
	return 0;
}

FeedersContext* CreateFiddersContext(char* _configFile)
{
	FeedersContext* fiddersContext = malloc(sizeof(FeedersContext));
	
	if(!fiddersContext)
	{
		return NULL;
	}
	
	if(!_configFile)
	{
		if(-1 == SetDefaultConfig(fiddersContext))
		{
			free(fiddersContext);
			return NULL;
		}
	}
	return fiddersContext;
}

/*function to create fidders threads with static routine function and FiddersContext */
int ExecuteFiddersThreads(FeedersContext* _context)
{
	pthread_t monitor;
	
	for(;;)
	{
	    NotifyCdrFile(_context);
	    pthread_create(&monitor, NULL, ReadCdrFile, _context);
	    pthread_join(monitor,NULL);
	}
	
	return 0;
}	
	
/*	
	for(i = 0; i < _context->m_numOfFeeders; ++i)
	{
		pthread_mutex_lock(&_context->m_mutex);
		while(!QueueIsEmpty(_context->m_cdrFilesQueue))
		{
			pthread_cond_wait(&_context->m_condVar, &_context->m_mutex);
		}
		pthread_mutex_unlock(&_context->m_mutex);
		pthread_create(&feeders[i], NULL, FeederRoutine, _context);
	}
	
	while(!_context->m_shutDownFlag)
	{		
		if(ReadLastMessage(_context->m_channel))
		{
			++_context->m_shutDownFlag;
			pthread_join(monitor,NULL);
			for(i=0; i < _context->m_numOfFeeders; ++i)
			{
				pthread_join(feeders[i],NULL);
				return 0;
			}
		}
	}
}

void* FeederRoutine(void* _context)
{

	char fileName[64];
	FILE* fp;	
	for(;;)
	{
		
		if(((FeedersContext*)_context)->m_shutDownFlag)
		{
			break;
		}
		pthread_mutex_lock(&((FeedersContext*)_context)->m_mutex);
		while(!QueueIsEmpty(((FeedersContext*)_context)->m_cdrFilesQueue))
		{
			pthread_cond_wait(&((FeedersContext*)_context)->m_condVar, &((FeedersContext*)_context)->m_mutex);	
		}
		pthread_mutex_unlock(&((FeedersContext*)_context)->m_mutex);
		QueueRemove(((FeedersContext*)_context)->m_cdrFilesQueue, &fileName);
		fp= fopen(fileName, "r");
		ReadCdrFile(fp, ((FeedersContext*)_context)->m_channel);
		fclose(fp);	
	}
	return NULL;
}

void* Monitor(void* _context)
{

	char* cdrFile[128];	
	char buffer[64];
	size_t i = 0;

	for(;;)
	{
		if(((FeedersContext*)_context)->m_shutDownFlag)
		{
			break;
		}
		NotifyCdrFile(((FeedersContext*)_context)->m_recPath,buffer);
		cdrFile[i] = malloc(sizeof(buffer));
		strcpy(cdrFile[i], buffer);
		QueueInsert(((FeedersContext*)_context)->m_recPath, (void*)cdrFile[i]);
		pthread_cond_broadcast(&((FeedersContext*)_context)->m_condVar);
		++i;
	}
	return NULL;
}
*/
