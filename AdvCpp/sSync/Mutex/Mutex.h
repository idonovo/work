#ifndef __MYMUTEX_H__
#define __MYMUTEX_H__

#ifdef WIN32
	#include "Windows.h" 
	#include <memory>
	typedef CRITICAL_SECTION  mutex_t;
#elif defined __linux__
	#include <pthread.h>
	typedef  pthread_mutex_t mutex_t;
#endif

namespace advcpp
{

class Mutex
{

friend class Condition_variable;

public:
	explicit Mutex();
	~Mutex ();
	
	void Lock();
	void Unlock();
	
private:
	Mutex(const  Mutex&);
	Mutex& operator=(const Mutex&);
	 
	mutex_t m_mutex; 
};

}
#endif /* __MYMUTEX_H__ */

