#include <time.h>   
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

#include "../../inc/logger.h"
#include "../../inc/config.h"

#define BUFFERSIZE 32
#define LOG_PRINTFORMAT "%s %d %lu %c %s %s @ %s %d %s\n"
#define LOG_PRINT_PARAMETERS buffer, LogD->m_pid, pthread_self(), levelsArray[_logLevel], LogD->m_moduleName, _fileName, _funcName ,_line, _message


/*
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvariadic-macros"

#define EPRINT(...) fprintf(stderr, __VA_ARGS__)

#pragma GCC diagnostic pop

*/

typedef FILE* Log; 

typedef struct LogData
{
	ConfigData*  m_confData;
	int		 	 m_logLevel;
	int   		 m_pid;
	Log   		 m_log;
	char*  		 m_moduleName;
}LogData;

typedef LogData* LogDa; 

static LogDa  LogD = NULL;

const char levelsArray[8] = {'T', 'D', 'I', 'W', 'E', 'C', 'S', 'F'};

/* function to identify a log level from config. data */
int FindLogLevel(char _level);
/* function to create a log if didnt create yet */
static void CreateLog(char* _configFileName);
/* function to init value in a log, once created*/
static void InitLog(LogData* _logData);
/* function to get current time for printing */
static void GetTime(char* _buffer);
/* function to check if the user log level matches cofiguration*/
static int IsValidLogLevel(int _CurLogLevel);
/* functions to destroy and free logger*/
static void LogDestroy(LogData* _logData);
static void LogClose();


/***********************************************************/
int FindLogLevel(char _level)
{
	int i;
	
	for(i=0; i<8; ++i)
	{
		if(levelsArray[i] == _level)
		{
			break;	
		}
	}
	
	return i;
}

static void InitLog(LogData* _logData)
{
	LogD->m_log = fopen(LogD->m_confData->m_logFileName, "a+");
	
	if (LogD->m_log == NULL)
	{
		/* return some error */
	}
	
	if(atexit(&LogClose) < 0)
	{
		/* return some error */
	}
	
	LogD->m_logLevel = FindLogLevel(LogD->m_confData->m_level);
	LogD->m_moduleName = LogD->m_confData->m_modulName;
	LogD->m_pid= getpid();
	return;
	

}

static void CreateLog(char* _configFileName)
{
	
	LogD = malloc(sizeof(LogData));
	
	if (LogD == NULL)
	{
		/* return some error */
	}
	
	LogD->m_confData= malloc(sizeof(ConfigData));
	
	if (LogD->m_confData == NULL)
	{
		/* return some error */
	}
	
	GetConfig(LogD->m_confData, _configFileName);
	InitLog(LogD);
	
	return;
}

LogData* GetLog(char* _configFileName)
{
		
	if(LogD!= NULL)
	{
		return LogD;
	}
	CreateLog(_configFileName);
	
	return LogD;

}
/***********************************************************/
static void GetTime(char* _buffer)
{
	time_t rawtime;
  	struct tm * timeinfo;
  	
  	time (&rawtime);
	timeinfo = localtime (&rawtime);
  	strftime (_buffer,BUFFERSIZE,"%Y-%m-%d %H:%M:%S.000",timeinfo);

}

static int IsValidLogLevel(int _CurLogLevel)
{
	return _CurLogLevel < LogD->m_logLevel? 0 : 1; 
}

void LogWrite(LogData* _logData, int _logLevel, const char* _funcName, int _line, const char* _fileName, const char* _message)
{

    char buffer[BUFFERSIZE];
    
    if(!IsValidLogLevel(_logLevel))
    {
    	return;
    }

    GetTime(buffer); 
  
	fprintf(LogD->m_log, LOG_PRINTFORMAT, LOG_PRINT_PARAMETERS);
	return;
}
/***********************************************************/
static void LogDestroy(LogData* _logData)
{
	fclose(LogD->m_log);
	LogD->m_log = NULL;
	free(LogD->m_confData);
	free(LogD);
}

static void LogClose()
{

	if(NULL == LogD->m_log)
	{
		return;
	} 
	LogDestroy(LogD);
}

/***************************************************************/
