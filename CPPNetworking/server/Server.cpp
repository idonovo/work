#include "Server.h"
#include "Application.h"
#include "NetworkErr.h"
#include <algorithm> 

namespace Netcpp
{


Server::Server(const Peer_info& _info, std::tr1::shared_ptr<Application>  _app, std::size_t _queueSize):
m_acceptor(new SocketAcceptor(_info)),
m_app(_app),
m_queueSize(_queueSize),
m_isRunning(false)
{
	m_acceptor->SetNonBlocking();
	m_acceptor->Listen(_queueSize);
}

Server::~Server ()
{
	delete m_acceptor;
}

void Server::Run()
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

void Server::SerchForClientMessage()
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

std::size_t Server::SendMessage(const Peer_info& _info, std::tr1::shared_ptr<SocketStream> _stream)
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

bool Server::DeleteClient(const Peer_info& _info)
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

