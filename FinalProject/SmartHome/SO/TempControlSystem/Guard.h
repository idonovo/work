#ifndef __GUARD_H__
#define __GUARD_H__

#include <pthread.h>


class Guard
{
public:
    Guard(pthread_mutex_t* _mutex)
    {
    	if(_mutex)
    	{
			m_mutex =_mutex;
			pthread_mutex_lock(m_mutex);
    	}
    }

	~Guard ()
	{
		 pthread_mutex_unlock(m_mutex);
	}
        
private:
	Guard (const Guard& arguments);
    Guard&operator=(const Guard& arguments);
	
	pthread_mutex_t*	m_mutex;
};
#endif /* __GUARD_H__ */

