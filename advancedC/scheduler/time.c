#include "mytime.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define MILI_FACTOR 1000000
#define BILLION 1000000000
#define MICRO_FACTOR 1000
#define SECONDS tv_sec
#define NANO tv_nsec


struct Time
{
	struct timespec	m_time;
	clockid_t m_clockID;
};

/***************************************************/
Time* CreateTime(const clockid_t _clockID)
{
    Time* newTime = malloc(sizeof(Time));
	if(!newTime)
	{
		return NULL;
	}
	newTime->m_clockID = _clockID;
	
	return newTime;
}

/**************************************************/
int TimeGetNextInterval(Time* _intervalTime, int _milliSecs)
{
	int flag; 

	if(!_intervalTime)
	{
		return 0;
	}

	flag = clock_gettime(_intervalTime->m_clockID, &(_intervalTime->m_time));
	if(!flag)
	{
		return 0;
	}

	if((_intervalTime->m_time.NANO + (_milliSecs*MILI_FACTOR)) > BILLION)
	{
		_intervalTime->m_time.SECONDS += ((_intervalTime->m_time.NANO + (_milliSecs*MILI_FACTOR)) / BILLION);
		_intervalTime->m_time.NANO = ((_intervalTime->m_time.NANO + (_milliSecs*MILI_FACTOR)) % BILLION);
			
		return 1;
	}
	_intervalTime->m_time.NANO += (_milliSecs*MILI_FACTOR);

	return 1;
}

/***************************************************/	
void TimeDestroy(Time* _time)
{
	if(!_time)
	{
		free(_time);
	}
}

/***************************************************/

int	TimeCompare(const Time* _first, const Time* _second)
{
	if( _first->m_time.SECONDS == _second->m_time.SECONDS)
	{
		return (_first->m_time.NANO >_second->m_time.NANO? 1: 0);
	}
	return (_first->m_time.SECONDS >_second->m_time.SECONDS? 1: 0);

}

/***************************************************/
void TimeSleepUntil(const Time* _tasktime)
{
	struct timespec t;
	long secDif;
	long microDif;
	
	clock_gettime(_tasktime->m_clockID, &t);
	
	secDif = _tasktime->m_time.SECONDS - t.SECONDS;

	if(secDif >=0)
	{
		if((microDif = (secDif * MICRO_FACTOR) + ((_tasktime->m_time.NANO - t.NANO)/MICRO_FACTOR)) > 0) 
		usleep((unsigned long)microDif);
	}
	return;		
}	


