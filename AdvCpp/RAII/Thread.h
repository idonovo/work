#ifndef __MYTHREAD_H__
#define __MYTHREAD_H__

#include <stdlib.h>
#include <string.h>
#include <stdexcept>
#include <errno.h>
#include <pthread.h>
#include <cstddef>

namespace advcpp
{

template<class T>
class Thread
{

public:
	explicit Thread (T*);
	~Thread ();
	
	std::size_t	GetID() const;
	void		Cancel();
	void        Detach();
	void		Join();
	bool        IsRunning()const;
	bool        IsJoinable()const;
	static T*   Lounch(T* _context);
	
private:
	Thread(const Thread&);
	Thread& operator=(const Thread&);
	
	T* m_obj;
	pthread_t   threadID;
	bool        isJoinable;
	bool        isSafeToExit;
};

template<class T>
inline T* Thread<T>::Lounch(T* _context)
{
	
	_context->Run();
	return _context;
}

template<class T>
inline Thread<T>::Thread (T* _obj):m_obj(_obj)
{
	if(pthread_create(&threadID, 0, (void * (*)(void *))Lounch, m_obj))
	{
		throw std::runtime_error(strerror(errno));
	}
	isSafeToExit = false;
	isJoinable = true;
}

template<class T>
inline Thread<T>::~Thread ()
{
    if(!isSafeToExit)
    {
        abort();
    }
}

template<class T>
inline std::size_t Thread<T>::GetID()const
{
	return threadID;
}

template<class T>
inline bool Thread<T>::IsJoinable()const
{
	return isJoinable;
}

template<class T>
inline void Thread<T>::Cancel()
{
	 if(pthread_cancel(threadID))
	 {
	 	throw std::runtime_error(strerror(errno));
	 }
	 isJoinable = false;
	 isSafeToExit = true;
}

template<class T>
bool Thread<T>::IsRunning()const
{
    return m_obj->IsRunning();
}

template<class T>
inline void Thread<T>::Join()
{
	if(pthread_join(threadID, 0))
	{
	 	throw std::runtime_error(strerror(errno));
	}
	isSafeToExit = true;
	isJoinable = false;
}

template<class T>
inline void Thread<T>:: Detach()
{
    if(pthread_detach(threadID))
	{
	 	throw std::runtime_error(strerror(errno));
	}
	isJoinable = false;
	isSafeToExit = true;
}

}

#endif /* __MYTHREAD_H__ */

