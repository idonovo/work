#include <string.h>
#include <stdexcept>
#include <errno.h>

#include "CondVar.h"

namespace advcpp
{
Condition_variable::Condition_variable()
{
	if(pthread_cond_init(&m_cond, NULL))
	{
		throw std::runtime_error(strerror(errno));
	}
}

Condition_variable::~Condition_variable ()
{
	pthread_cond_destroy(&m_cond);
}

void Condition_variable:: Wait(Mutex& _m)
{
	if(pthread_cond_wait(&m_cond, &_m.mutex))
	{
		throw std::runtime_error(strerror(errno));
	}
}

template<class Predicate>
void Condition_variable::Wait(Mutex& _m, Predicate _t)
{
	while(!_t)
	{	
		if(pthread_cond_wait(&m_cond, &_m.mutex))
		{
			throw std::runtime_error(strerror(errno));
		}
	}
}

void Condition_variable:: Notify_one()
{
	if(pthread_cond_signal(&m_cond))
	{
		throw std::runtime_error(strerror(errno));
	}
}

void Condition_variable:: Notify_all()
{
	if(pthread_cond_broadcast(&m_cond))
	{
		throw std::runtime_error(strerror(errno));
	}
}	

}

