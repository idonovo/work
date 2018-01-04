#ifndef __MYSERVER_H__
#define __MYSERVER_H__

#include "SocketAcceptor.h"
#include "SocketStream.h"
#include "Peer_info.h"
#include "Application.h"
#include "NetworkErr.h"
#include <algorithm> 
#include <list>


namespace Netcpp
{

class Application;

template <class T>
class Server
{
public:
	Server(const Peer_info&, std::tr1::shared_ptr<T> , std::size_t _queueSize);
	virtual ~Server ();
	
	virtual void Run();
	void Stop();
	std::size_t SendMessage(const Peer_info&, std::tr1::shared_ptr<SocketStream>);

private:
	Server(const Server&);
	Server& operator=(const Server&);
	

protected:
	void SerchForClientMessage();
	bool DeleteClient(const Peer_info&);
	SocketAcceptor*	m_acceptor;
	std::tr1::shared_ptr<T> m_app;
	std::list<std::tr1::shared_ptr<Socket> > m_socketsList;
	std::size_t m_queueSize;
	bool m_isRunning;
};	

template <class T>
Server<T>::Server(const Peer_info& _info, std::tr1::shared_ptr<T>  _app, std::size_t _queueSize):
m_acceptor(new SocketAcceptor(_info)),
m_app(_app),
m_queueSize(_queueSize),
m_isRunning(false)
{
	m_acceptor->SetNonBlocking();
	m_acceptor->Listen(_queueSize);
}

template <class T>
Server<T>::~Server ()
{
	delete m_acceptor;
}

template <class T>
inline void Server<T>::Run()
{
	m_isRunning = true;
	std::tr1::shared_ptr<Socket> newSock;
	
	while(m_isRunning)
	{
		
		try
        {
			newSock = m_acceptor->Accept();
		    newSock->SetNonBlocking();	
		    if(m_app->ApproveClient(newSock))
		    {
			    m_socketsList.push_front (newSock);							
		    }
        }
        catch(Err_TryAgain& err)
        {}
	
		SerchForClientMessage();
	}
}

template <class T>
inline void Server<T>::SerchForClientMessage()
{
	
	std::tr1::shared_ptr<SocketStream> ptrStream;
	
	for (std::list<std::tr1::shared_ptr<Socket> >::iterator it = m_socketsList.begin(); it !=  m_socketsList.end(); it++)
	{
		try
		{	
			ptrStream =  (*it)->Recv();
			std::cout << "got message" << ptrStream.get();
			m_app->PushSocketStream(ptrStream);
		}
		catch(Err_TryAgain& err){}
		catch(Err_Disconnected& disErr)
		{
			 it = m_socketsList.erase(it);
			 --it;
		}
	}
}

template <class T>
inline std::size_t Server<T>::SendMessage(const Peer_info& _info, std::tr1::shared_ptr<SocketStream> _stream)
{
	for (std::list<std::tr1::shared_ptr<Socket> >::iterator it = m_socketsList.begin(); it !=  m_socketsList.end(); ++it)
	{
		if((*it)->GetPeerInfo() == _info)
		{
			
			return (*it)->Send(_stream);
		}
	}
	return 0;
}

template <class T>
inline bool Server<T>::DeleteClient(const Peer_info& _info)
{
	for (std::list<std::tr1::shared_ptr<Socket> >::iterator it = m_socketsList.begin(); it !=  m_socketsList.end(); ++it)
	{
		if((*it)->GetPeerInfo() == _info)
		{
			 m_socketsList.erase(it);
			 return true;
		}
	}
	return false;
}

}
#endif /* __MYSERVER_H__ */


