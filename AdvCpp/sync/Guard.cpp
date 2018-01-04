#include "Guard.h"


namespace advcpp
{

Guard::Guard(IMutex& _mutex): m_mutex(_mutex)
{
	m_mutex.Lock();
}

Guard::~Guard()
{
	m_mutex.Unlock();
}	


}

