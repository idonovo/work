#include "stdafx.h"
#include <string.h>
#include <stdexcept>
#include <errno.h>

#include "CondVar.h"

namespace advcpp
{
Condition_variable::Condition_variable()
{
	#ifdef __linux__	
	if(pthread_cond_init(&m_cond, NULL))
	{
		throw std::runtime_error(strerror(errno));
	}
	#elif defined WIN32
	InitializeConditionVariable(&m_cond);
	#endif
}

Condition_variable::~Condition_variable ()
{
	#ifdef __linux__
	pthread_cond_destroy(&m_cond);
	#elif defined WIN32
	#endif
}

void Condition_variable:: Wait(Mutex& _m)
{
	#ifdef __linux__
	if(pthread_cond_wait(&m_cond, &_m.m_mutex))
	{
		throw std::runtime_error(strerror(errno));
	}
	#elif defined WIN32
	SleepConditionVariableCS(&m_cond, &_m.m_mutex, INFINITE);
	#endif
}

template<class Predicate>
void Condition_variable::Wait(Mutex& _m, Predicate _t)
{
	
	while(!_t)
	{	
		#ifdef __linux__
		if(pthread_cond_wait(&m_cond, &_m.mutex))
		{
			throw std::runtime_error(strerror(errno));
		}
		#elif defined WIN32
			SleepConditionVariableCS(&m_cond, &_m.m_mutex, INFINITE);
		#endif
	}
}

void Condition_variable:: Notify_one()
{
	#ifdef __linux__
	if(pthread_cond_signal(&m_cond))
	{
		throw std::runtime_error(strerror(errno));
	}
	#elif defined WIN32
			WakeConditionVariable(&m_cond);
	#endif
	
}

void Condition_variable:: Notify_all()
{
	#ifdef __linux__
	if(pthread_cond_broadcast(&m_cond))
	{
		throw std::runtime_error(strerror(errno));
	}
	#elif defined WIN32
			WakeAllConditionVariable(&m_cond);
	#endif
}	

}

