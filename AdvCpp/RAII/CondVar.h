#ifndef __CONDVAR_H__
#define __CONDVAR_H__

#include "Mutex.h"
#include <pthread.h>

//class Mutex;
namespace advcpp
{

class Condition_variable
{
public:
	Condition_variable ();
	~Condition_variable ();
	
	void 	Wait(Mutex&);
	template<class Predicate>
	void 	Wait(Mutex&, Predicate _t);
	void	Notify_one();
	void	Notify_all();

private:
	Condition_variable(const Condition_variable&);
	Condition_variable& operator=(const Condition_variable&);
	
	
	pthread_cond_t m_cond;
};

}
#endif /* __CONDVAR_H__ */

