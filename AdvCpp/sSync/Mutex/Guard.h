#ifndef __GUARD_H__
#define __GUARD_H__

#include "Mutex.h"

namespace advcpp
{

class Guard
{
public:
    Guard(Mutex& _mutex);
	~Guard ();
        
private:
	Guard (const Guard& arguments);
    Guard&operator=(const Guard& arguments);
	
	Mutex&	m_mutex;
};

} // namespace
#endif /* __GUARD_H__ */
