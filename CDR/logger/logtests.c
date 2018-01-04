
#include <stdio.h>

#include "../../inc/logger.h"

void SimpleLogCreate()
{
	LogData*  LogD;
	int i; 

    for(i=0; i<10; ++i)
    {
	    LogD = GetLog("simpleConf.txt");
	    LogWrite(LogD, LOG_ERROR,  __func__,  __LINE__, "SimpleLogCreate", "i am tired");
    }
    return;

}

void MessyConfDocLogCreate()
{
	LogData*  LogD;
	int i; 

    for(i=0; i<10; ++i)
    {
	    LogD = GetLog("messyConf.txt");
	    LogWrite(LogD, LOG_FATAL,  __func__,  __LINE__, "MessyLogCreate", "i am tired");
    }
    return;

}

void LogCreateWithDefaultConf()
{
	LogData*  LogD;
	int i; 

    for(i=0; i<10; ++i)
    {
	    LogD = GetLog(NULL);
	    LogWrite(LogD, LOG_CRITICAL,  __func__,  __LINE__, "default", "i am tired");
    }
    return;

}

void IsLogWriteUnderLevelConfg()
{
	LogData*  LogD;
	int i; 

    for(i=0; i<10; ++i)
    {
	    LogD = GetLog("simpleConf.txt");
	    LogWrite(LogD, LOG_TRACE,  __func__,  __LINE__, "SimpleLogCreate", "i am tired");
    }
    return;

}



int main()
{
	SimpleLogCreate();
	MessyConfDocLogCreate();
	LogCreateWithDefaultConf();
	
	return 0;

}
