#ifndef __MYTHREAD_H__
#define __MYTHREAD_H__

#include <stdlib.h>
#include <string.h>
#include <stdexcept>
#include <errno.h>
#include <cstddef>
#include "Mutex.h"
#include "Guard.h"

#ifdef WIN32
	#include "Windows.h" 
	#include <memory>
//	typedef CRITICAL_SECTION  mutex_t;
	typedef	HANDLE Thread_ID;
#elif defined __linux__
	#include <pthread.h>
//	typedef  pthread_mutex_t mutex_t;
	typedef pthread_t  Thread_ID;
#endif


namespace advcpp
{

template<class T>
class Thread
{

public:
	
#ifdef __linux__
	static std::tr1::shared_ptr<T>  Lounch(T*);
#elif WIN32
	static DWORD Lounch(LPVOID);
#endif


	explicit Thread (T*);
	~Thread ();
	std::size_t	GetID() const;
	
#ifdef __linux__
	void		Cancel();
	void        Detach();
#endif

	void		Join();
	bool        IsRunning()const;
	bool        IsJoinable()const;
	
private:
	Thread(const Thread&);
	Thread& operator=(const Thread&);
	
	T*	m_obj;
	Thread_ID   threadID;
	Mutex		m_mutex;
	bool        isJoinable;
	bool        isSafeToExit;
};

#ifdef  __linux__
template<class T>
inline std::tr1::shared_ptr<T>  Thread<T>::Lounch(T* _context)
{
	_context->Run();
	return _context;
}
#endif

template<class T>
#ifdef WIN32
inline DWORD Thread<T>::Lounch(LPVOID _context)
{
	((T*)_context)->Run();
	return 0;
}
#endif

template<class T>
inline Thread<T>::Thread (T*  _obj):m_obj(_obj), isJoinable (true), isSafeToExit(false)
{
	
#ifdef __linux__
	if(pthread_create(&threadID, 0, (void * (*)(void *))Lounch, m_obj))
	{
		throw std::runtime_error(strerror(errno));
	}
#endif
	
#ifdef WIN32
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Lounch, (LPVOID)m_obj, 0 , 0);
#endif
}

template<class T>
Thread<T>::~Thread ()
{
    Guard guard(m_mutex);
    if(!isSafeToExit)
    {
        std::abort();
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

#ifdef  __linux__
template<class T>
inline void Thread<T>::Cancel()
{
	 Guard guard(m_mutex);
	 if(pthread_cancel(threadID))
	 {
	 	throw std::runtime_error(strerror(errno));
	 }
	 isJoinable = false;
	 isSafeToExit = true;
}
#endif

template<class T>
bool Thread<T>::IsRunning()const
{
    return m_obj->IsRunning();
}

template<class T>
inline void Thread<T>::Join()
{
	Guard guard(m_mutex);
	if(isJoinable)
	{
		#ifdef __linux__
		if(pthread_join(threadID, 0))
		{
		 	throw std::runtime_error(strerror(errno));
		}
		#elif WIN32
			WaitForSingleObject(threadID, INFINITE); 
			CloseHandle(threadID);

		#endif
		isSafeToExit = true;
		isJoinable = false;
	}
}

#ifdef  __linux__
template<class T>
inline void Thread<T>:: Detach()
{
    Guard guard(m_mutex);
    if(pthread_detach(threadID))
	{
	 	throw std::runtime_error(strerror(errno));
	}
	isJoinable = false;
	isSafeToExit = true;
}
#endif

}

#endif /* __MYTHREAD_H__ */
