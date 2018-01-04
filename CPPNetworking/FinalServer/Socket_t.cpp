#include "Socket_t.h"
#include <stdexcept>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>  
#include <sys/socket.h>


namespace Netcpp
{

Socket_t::Socket_t()
{
	InitSocket();
}
Socket_t::Socket_t (const fd_t& _fd): m_fd(_fd){}

Socket_t::Socket_t (int _fd):m_fd(_fd){}
	
Socket_t::~Socket_t ()
{
	close(m_fd);
}

void Socket_t::SetBlockingMode(BlokingMode _mode)
{
	m_mode = _mode;
	if(_mode == Non_blocking)
	{
		int flags;
		if(-1 ==(flags = fcntl(m_fd, F_GETFL)))
		{
			throw std::runtime_error(strerror(errno));
		}

		if(-1 == fcntl(m_fd, F_SETFL, flags | O_NONBLOCK))
		{
			throw std::runtime_error(strerror(errno));
		}
	}
	else
	{
		close(m_fd);
		
	
	}
}

void Socket_t::InitSocket()
{
	int optval= 1;
	int sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock< 0) 
    {    	
		throw std::runtime_error(strerror(errno));
    }
    
	if(-1 == setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)))
	{
		throw std::runtime_error(strerror(errno));
	}
	
	m_fd =  sock;

}

const fd_t& Socket_t::GetFd_t() const
{
	return m_fd;
}

}



