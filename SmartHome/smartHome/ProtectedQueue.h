#ifndef __QUEUEPRO_H__
#define __QUEUEPRO_H__

#include "Guard.h"

#include <semaphore.h>
#include <pthread.h>   
#include <queue>


template <class T>
class ProtectedQueue
{
public:
    
    ProtectedQueue(unsigned int _x=100)
    {
        sem_init(&m_full, 0, 0);
        sem_init(&m_empty, 0, _x);
  		pthread_mutex_init(&m_mutex, 0);
    }
    
    virtual ~ProtectedQueue()
    {
        pthread_mutex_destroy(&m_mutex);
        sem_destroy(&m_full);
        sem_destroy(&m_empty);
	}
    
    void Insert(const T _t)
    {
        sem_wait(&m_empty);
     	Guard guard(&m_mutex);
        procQueue.push(_t);
	    sem_post(&m_full);
    }
    
    void Remove(T* _t)
    {
        sem_wait(&m_full);
        Guard guard(&m_mutex);
        *_t = procQueue.front();
        procQueue.pop();
        sem_post(&m_empty);
    }

private:
	ProtectedQueue(ProtectedQueue& prot);
	ProtectedQueue& operator=(ProtectedQueue& proc);

private:
    std::queue<T> procQueue;
    sem_t	m_full;
    sem_t	m_empty;
    pthread_mutex_t	m_mutex;
};

#endif /* __QUEUEPRO_H__ */

