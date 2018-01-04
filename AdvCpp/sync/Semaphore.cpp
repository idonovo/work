#include "Semaphore.h"
#include <string.h>
#include <stdexcept>
#include <errno.h>

namespace advcpp
{

Semaphore::Semaphore(std::size_t nVal): ISemaphore()
{
   Start();
}


Semaphore::~Semaphore()
{
   sem_destroy(m_pSemId);
   delete m_pSemId;
}


void Semaphore:: Start()
{  
    if(!isStart)
    {
        m_pSemId = new sem_t;
        if (sem_init(m_pSemId, 0, m_nVal) == -1)
        {
            throw std::runtime_error(strerror(errno));
        }
        isStart  = true;
        isStop  = false;
    }
}

void Semaphore::Post()
{
    if (sem_post(m_pSemId) == -1)
    {
        throw std::runtime_error(strerror(errno));
    }
}

void Semaphore::TryWait()
{
    if (sem_trywait(m_pSemId) == -1)
    {
        throw std::runtime_error(strerror(errno));
    }
}

void Semaphore::Stop()
{
    if (sem_destroy(m_pSemId)== -1)
    {
        throw std::runtime_error(strerror(errno));
    }
    isStart  = false;
    isStop  = true;
}

bool Semaphore::IsStop()const
{
    return isStop;
}

bool Semaphore::IsStart()const
{
    return  isStart;
}

void Semaphore::Wait()
{
    if(sem_wait(m_pSemId) == -1)
	{
		throw std::runtime_error(strerror(errno));
	}
}

}
