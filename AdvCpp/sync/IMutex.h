#ifndef __MYIMUTEX_H__
#define __MYIMUTEX_H__

//#include <boost/core/noncopyable.hpp>
namespace advcpp
{

class IMutex//: //private boost::noncopyable
{
public:
    IMutex(){}
    virtual ~IMutex() {}

	virtual void Lock()     =0;
	virtual void Unlock()   =0;
};

}
#endif /* __MYIMUTEX_H__ */

