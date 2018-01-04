#include "stdafx.h"
#include "Guard.h"


namespace advcpp
{

Guard::Guard(Mutex& _mutex): m_mutex(_mutex)
{
	m_mutex.Lock();
}

Guard::~Guard()
{
	m_mutex.Unlock();
}	


}

