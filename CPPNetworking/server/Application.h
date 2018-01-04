#ifndef __MYAPPLICATION_H__
#define __MYAPPLICATION_H__

#include "SocketStream.h"
#include <iostream>

namespace Netcpp
{

class Application
{
public:
	Application (){}
	virtual ~Application (){}
	
	bool ApproveClient(std::tr1::shared_ptr<Socket>){return true;}
	void PushSocketStream(std::tr1::shared_ptr<SocketStream> _stream){std::cout << (_stream.get()) << std::endl;}
private:
	/* data */
};
}

#endif /* __MYAPPLICATION_H__ */

