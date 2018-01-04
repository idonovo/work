#ifndef __MYSERVER_H__
#define __MYSERVER_H__

#include "SocketAcceptor.h"
#include "SocketStream.h"
#include "Peer_info.h"
#include <list>


namespace Netcpp
{

class Application;

class Server
{
public:
	Server(const Peer_info&, std::tr1::shared_ptr<Application> , std::size_t _queueSize);
	virtual ~Server ();
	
	virtual void Run();
	void Stop();
	std::size_t SendMessage(const Peer_info&, std::tr1::shared_ptr<SocketStream>);

private:
	Server(const Server&);
	Server& operator=(const Server&);
	
	void SerchForClientMessage();
	bool DeleteClient(const Peer_info&);
	
	SocketAcceptor*	m_acceptor;
	std::tr1::shared_ptr<Application> m_app;
	std::list<std::tr1::shared_ptr<Socket> > m_socketsList;
	std::size_t m_queueSize;
	bool m_isRunning;
};	

}
#endif /* __MYSERVER_H__ */


