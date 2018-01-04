#ifndef __MISINGLTON_H__
#define __MISINGLTON_H__

#include <tr1/memory>	
#include "pthread.h"
#include "Guard.h"

/*******************************************************/
//Desc.: Templated thread safe singleton which provides asingle accecces to an object of type T.
// An effective use of the Singleton requiers that the Constructors of T class will be private and the Singleton class wi be a friend of T class. In addition, the singleton can work only with default constructor with no arguments from user. 
/*******************************************************/


namespace advcpp
{

template <class T>
class Singleton
{
	
public:
	static std::tr1::shared_ptr<T> GetInstance();
	
private:
	explicit Singleton();
	Singleton(const Singleton&);
	Singleton& operator= (const Singleton&);
	
protected:
	~Singleton();
	
	static std::tr1::shared_ptr<T> 	m_instance;
	static pthread_mutex_t 		m_mutex;
	static volatile int			m_initComplete;

};

template <class T>
std::tr1::shared_ptr<T> Singleton<T>::m_instance;

template <class T>
pthread_mutex_t Singleton<T>::m_mutex = PTHREAD_MUTEX_INITIALIZER;

template <class T>
volatile int Singleton<T>::m_initComplete = 0;

template <class T>
std::tr1::shared_ptr<T> Singleton<T>::Singleton::GetInstance()
{

	if(__sync_bool_compare_and_swap (&m_initComplete, 0, 0))
	{
		Guard guard(&m_mutex);
		if(__sync_bool_compare_and_swap (&m_initComplete, 0, 0))
		{
			m_instance = std::tr1::shared_ptr<T>(new T);
			__sync_fetch_and_add (&m_initComplete, 1);
		}
	}
	return m_instance;
}

template <class T>
Singleton<T>::Singleton()
{
	m_instance(new T);
}

} //namespace
#endif /* __MISINGLTON_H__ */

