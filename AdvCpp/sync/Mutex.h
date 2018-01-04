#ifndef __MYMUTEX_H__
#define __MYMUTEX_H__

#include <pthread.h>
#include <cstddef>
#include "IMutex.h"

namespace advcpp
{


class Mutex: public IMutex
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
	 
	 pthread_mutex_t mutex;
};


}
#endif /* __MYMUTEX_H__ */

