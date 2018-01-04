#ifndef __MYSEMAPHORE_H__
#define __MYSEMAPHORE_H__

#include <cstddef>
#include <semaphore.h>
#include "ISemaphore.h"

namespace advcpp
{

class Semaphore : public ISemaphore
{

public:
    Semaphore(std::size_t nVal);
    ~Semaphore();
    virtual void Start();
    virtual void Wait();
    virtual void Post();
    virtual void TryWait();
    virtual void Stop();
    virtual bool IsStop()const;
    virtual bool IsStart()const;

private:
    Semaphore(const Semaphore&);
    Semaphore& operator=(const Semaphore&);
    
    sem_t * m_pSemId;
    unsigned int m_nVal;
    bool isStop;
    bool isStart;
};

}
#endif /* __MYSEMAPHORE_H__ */

