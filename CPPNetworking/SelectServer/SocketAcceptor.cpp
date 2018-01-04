#include "SocketAcceptor.h"
#include "NetworkErr.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>


namespace Netcpp
{

SocketAcceptor:: SocketAcceptor (const Peer_info& _info):
m_socket(CreateChannel()),
m_info(_info), 
m_isListening(false)
{}

SocketAcceptor::~SocketAcceptor()
{
    if(!m_socket)
    {
        close(m_socket);
    }
}

fd_t&  SocketAcceptor::GetFD_t()
{
	return m_socket;
}

void SocketAcceptor::SetNonBlocking()
{
	int flags;
    if(-1 ==(flags = fcntl(m_socket, F_GETFL)))
    {
    	throw std::runtime_error(strerror(errno));
    }
    
    if(-1 == fcntl(m_socket, F_SETFL, flags | O_NONBLOCK))
    {
    	throw std::runtime_error(strerror(errno));
    }
}
	
bool SocketAcceptor::Listen(std::size_t _size)
{
    if(m_isListening)
    {
        return m_isListening;
    }
    
    struct sockaddr_in m_addr;
    
	InitSocketAddr(&m_addr, m_info);
	try
	{
	    Bind(m_socket, &m_addr);
	    StartListening(m_socket, _size);
	    
	}catch(std::runtime_error err){
	
	    throw std::runtime_error("Too cool to listen");
	}
	
	m_isListening = true;
	
	return m_isListening;
}

void SocketAcceptor::Bind(fd_t _socket, struct sockaddr_in* m_addr)
{
	if(0 > bind(_socket , (struct sockaddr *) m_addr, sizeof(struct sockaddr_in)))
 	{
		throw std::runtime_error(strerror(errno));
 	} 

}

void SocketAcceptor::StartListening(fd_t _socket, std::size_t _size)
{	
 	if (listen(_socket, _size) < 0)
    {
		throw std::runtime_error(strerror(errno));
 	} 
}

void SocketAcceptor::InitSocketAddr(struct sockaddr_in* m_addr, const Peer_info& _serverinfo)
{	
	memset(m_addr, 0, sizeof(struct sockaddr_in));
	m_addr->sin_family = AF_INET;
 	m_addr->sin_addr.s_addr = INADDR_ANY;
	m_addr->sin_port = htons(_serverinfo.m_port);
}

fd_t SocketAcceptor::CreateChannel(void)
{
    int optval= 1;
	fd_t sock(socket(PF_INET, SOCK_STREAM, 0));
    if(sock< 0) 
    {    	
		throw std::runtime_error(strerror(errno));
    }
    
	if(-1 == setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)))
	{
		throw std::runtime_error(strerror(errno));
	}
	
	return sock;
}

std::tr1::shared_ptr<Socket> SocketAcceptor::Accept()
{

    if(!m_isListening)
    {
        throw std::runtime_error("Acceptor not listening");
    }
    
    struct sockaddr_in m_addr;
    socklen_t len = sizeof(m_addr); 
    int sock = accept(m_socket, (struct sockaddr *)&m_addr, &len);
    
	if(sock < 0)
	{
		if(errno == EAGAIN || errno == EWOULDBLOCK)
 		{
 		    throw Err_TryAgain("nonblocking mode. sending has failed");
 		}
 		else
 		{
     		throw std::runtime_error(strerror(errno));
 		}
	}
	
	Peer_info info = m_addr;
	fd_t newSock(sock);
	std::tr1::shared_ptr<Socket> ptrSock(new Socket(newSock, info));
	return ptrSock;
}

}
