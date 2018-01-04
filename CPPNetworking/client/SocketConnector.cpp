#include "SocketConnector.h"
#include "Socket.h"
#include "NetworkErr.h"

#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

namespace Netcpp
{

SocketConnector::SocketConnector(){}

SocketConnector:: ~SocketConnector (){}

void SocketConnector::InitSocketAddr(struct sockaddr_in* m_addr, const Peer_info& _serverinfo)
{	
	memset(m_addr, 0, sizeof(struct sockaddr_in));
	m_addr->sin_family = AF_INET;
	m_addr->sin_port = htons(_serverinfo.m_port);
    m_addr->sin_addr.s_addr = inet_addr(_serverinfo.m_ip.c_str());
}

fd_t SocketConnector::CreateChannel(void)
{
    int optval= 1;
	fd_t newfd(socket(PF_INET, SOCK_STREAM, 0));
    if(socket< 0) 
    {    	
		throw std::runtime_error(strerror(errno));
    }
    
	setsockopt(newfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	
	return newfd;
}

std::tr1::shared_ptr<Socket> SocketConnector::Connect(const Peer_info& _info)
{
	struct sockaddr_in m_addr;
	InitSocketAddr(&m_addr, _info);
	fd_t newSocket = CreateChannel();

    if(0 > connect(newSocket, (struct sockaddr*)&m_addr, sizeof(struct sockaddr_in)))
    {
		throw std::runtime_error(strerror(errno));
	}
	
	std::tr1::shared_ptr<Socket> socket(new Socket(newSocket, _info));
	return socket;	
}


	
}

