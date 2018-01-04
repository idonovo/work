#include "Mutex.h"
#include <string.h>
#include <stdexcept>
#include <errno.h>

namespace advcpp
{

Mutex::Mutex(): IMutex()
{
	if(pthread_mutex_init(&mutex, NULL))
	{
		throw std::runtime_error(strerror(errno));
	}
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&mutex);
}

void Mutex::Lock()
{
	if(pthread_mutex_lock(&mutex))
	{
		throw std::runtime_error(strerror(errno));
	}
}

void Mutex::Unlock()
{
	if(pthread_mutex_unlock(&mutex))
	{
		throw std::runtime_error(strerror(errno));
	}
}

}
