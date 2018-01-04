// Mutex.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Mutex.h"
#include <string.h>
#include <stdexcept>
#include <errno.h>

namespace advcpp
{

Mutex::Mutex()
{
	#ifdef __linux__	
	if(pthread_mutex_init(&m_mutex, NULL))
	{
		throw std::runtime_error(strerror(errno));
	}
	#endif

	#ifdef WIN32
		
		InitializeCriticalSection(&m_mutex);			
	#endif
}

Mutex::~Mutex()
{
	#ifdef __linux__
	pthread_mutex_destroy(&m_mutex);
	#endif

	#ifdef WIN32		
	DeleteCriticalSection(&m_mutex);
	#endif

}

void Mutex::Lock()
{
	#ifdef __linux__
	if(pthread_mutex_lock(&m_mutex))
	{
		//throw std::runtime_error(strerror(errno));
	}
	#endif

	#ifdef WIN32
	EnterCriticalSection(&m_mutex);
	#endif
}

void Mutex::Unlock()
{
	#ifdef __linux__
	if(pthread_mutex_unlock(&m_mutex))
	{
		throw std::runtime_error(strerror(errno));
	}
	#endif

	#ifdef WIN32
	LeaveCriticalSection(&m_mutex);
	#endif
}

}
