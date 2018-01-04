#include "ServerSocket.h"
#include <stdexcept>
#include <errno.h>
#include <string.h>
#include <unistd.h>

namespace Netcpp
{

ServerSocket::ServerSocket():Socket_t(), m_queueSize(DEF_SOCKET_QUEUE_SIZE)
{
	InitServerSocket(m_queueSize);
}

ServerSocket:: ServerSocket(const Peer_info& _info, std::size_t _size):
Socket_t(), 
m_info(_info), 
m_queueSize(_size)
{
	InitServerSocket(m_queueSize);
}

ServerSocket:: ServerSocket(int _fd, const Peer_info& _info, std::size_t _size): 
Socket_t(_fd), 
m_info(_info), 
m_queueSize(_size)
{
	InitServerSocket(m_queueSize);
}

ServerSocket::~ServerSocket(){}

void ServerSocket::SetPeer_info(const Peer_info& _info)
{
	m_info = _info;
}

void ServerSocket::InitServerSocket(std::size_t _size)
{
	struct sockaddr_in m_addr;
	
	InitSocketAddr(&m_addr, m_info);
	Bind(&m_addr);
	StartListening(_size);
}

void ServerSocket::StartListening(std::size_t _size)
{	
 	if (listen(m_fd, _size) < 0)
    {
		throw std::runtime_error(strerror(errno));
 	} 
}

void ServerSocket::InitSocketAddr(struct sockaddr_in* m_addr, const Peer_info& _serverinfo)
{	
	memset(m_addr, 0, sizeof(struct sockaddr_in));
	m_addr->sin_family = AF_INET;
 	m_addr->sin_addr.s_addr = INADDR_ANY;
	m_addr->sin_port = htons(_serverinfo.m_port);
}

void ServerSocket::Bind(struct sockaddr_in* m_addr)
{
	if(0 > bind(m_fd , (struct sockaddr *) m_addr, sizeof(struct sockaddr_in)))
 	{
		throw std::runtime_error(strerror(errno));
 	} 
}

void ServerSocket::SetQueSize(std::size_t _size)
{
	m_queueSize = _size;
}

void  ServerSocket::ListenToNewPeerinfo(const Peer_info& _info)
{
	struct sockaddr_in m_addr;
	
	m_info = _info;
	InitSocketAddr(&m_addr, m_info);
	Bind(&m_addr);
	StartListening(m_queueSize);
}

bool ServerSocket::AcceptNewSocket(std::tr1::shared_ptr<Socket_t> _socket)
{
 	
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
//	std::tr1::shared_ptr<Socket_t> AcceptNewSocket(BlokingMode);
}

