#ifndef __MYPRIORITYQUEUE_H__
#define __MYPRIORITYQUEUE_H__

//#include <iostream>
#include <queue>  
#include <cstddef>
#include "Mutex.h"
#include "Guard.h"
#include "CondVar.h"

namespace advcpp
{

template <class T, class Container = std::vector<T>, class U = std::less<typename Container::value_type> >
class PriorityQueue
{

public:
	explicit PriorityQueue (std::size_t = 500);
	 ~PriorityQueue ();	 

    bool 				Empty();
    std::size_t 		Size();
    T 					TopAndPop();
    bool 				TryTopAndPop(T* _t);
    void				Push(T);

private:
	PriorityQueue (const PriorityQueue&);
	PriorityQueue& operator=(const PriorityQueue&);
	void	CopyQueue(const PriorityQueue&);
	
	std::priority_queue<T, Container, U> m_queue;
	std::size_t  m_size;
	Mutex	m_mutex;
	Condition_variable m_condVar;
};

/************************predicate for condVar*************************/
/***********************************************************/

template <class T, class Container = std::vector<T>, class U = std::less<typename Container::value_type> >
class QueuePredicate
{
    public:
    QueuePredicate(std::priority_queue<T, Container, U> & ref):m_queue(ref){}
    ~QueuePredicate(){}
    bool operator()(void) {return m_queue.Empty();}
    std::priority_queue<T, Container, U>& m_queue;
};
/***********************************************************/
/***********************************************************/

/***********************************************************/
/***********************************************************/

template <class T, class Container, class U >
PriorityQueue< T, Container, U >::PriorityQueue(std::size_t _size):m_size(_size){}

template <class T, class Container, class U >
PriorityQueue< T, Container, U >::~PriorityQueue(){}

template <class T, class Container, class U >
PriorityQueue< T, Container, U >::PriorityQueue (const PriorityQueue< T, Container, U >& _p): m_queue(_p.m_queue), m_size(_p.m_size){}

template <class T, class Container, class U >
PriorityQueue< T, Container, U >& PriorityQueue< T, Container, U >::operator=(const PriorityQueue< T, Container, U >& _p)
{
	if(this != &_p)
	{
		CopyQueue(_p);
	}
}

template <class T, class Container, class U >
void PriorityQueue< T, Container, U >::CopyQueue(const PriorityQueue< T, Container, U >& _p)
{
	 m_queue = _p.m_queue;
	 m_size = _p.m_size;
}

template <class T, class Container, class U >
bool PriorityQueue< T, Container, U >::Empty()
{
	Guard guard(m_mutex);
	return m_queue.empty();
}

template <class T, class Container, class U >
size_t PriorityQueue< T, Container, U >::Size()
{
	Guard guard(m_mutex);
	return m_queue.size();
}

template <class T, class Container, class U >
void PriorityQueue< T, Container, U >::Push(T _obj)
{
	Guard guard(m_mutex);
//	std::cout << "pushing" << std::endl;
	m_queue.push(_obj);
	m_condVar.Notify_one();
}
	
template <class T, class Container, class U >
T  PriorityQueue< T, Container, U >::TopAndPop()
{
	Guard guard(m_mutex);
	while(m_queue.empty())
	{
		m_condVar.Wait(m_mutex);
	}
//	std::cout << "poping" << std::endl;
	T temp = m_queue.top();
	m_queue.pop();
	return temp;
}

template <class T, class Container, class U >
bool PriorityQueue< T, Container, U >::TryTopAndPop(T* _t)
{
	Guard guard(m_mutex);
	if(m_queue.size())
	{
		*_t = m_queue.top();
		m_queue.pop();
		return true;
	}
	return false;
}


}
#endif /* __MYPRIORITYQUEUE_H__ */

