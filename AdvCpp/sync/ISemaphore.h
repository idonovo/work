#ifndef __MYISEMPHORE_H__
#define __MYISEMPHORE_H__

//#include <boost/core/noncopyable.hpp>

namespace advcpp
{

class ISemaphore//: // private boost::noncopyable
{
public:
    ISemaphore(){}
    virtual ~ISemaphore() {}
    virtual void Wait()             = 0;
    virtual void Post()             = 0;
    virtual void TryWait()          = 0;
    virtual void Stop()             = 0;
    virtual void Start()            = 0;
    virtual bool IsStop()const      = 0;
    virtual bool IsStart()const     = 0;
};

}
#endif /* __MYISEMPHORE_H__ */

