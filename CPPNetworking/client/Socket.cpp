#include "Socket.h"
#include <stdexcept>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include "NetworkErr.h"

namespace Netcpp
{

Socket::Socket (fd_t _fd, const Peer_info& _peerinfo): 
m_socket(_fd), 
m_info(_peerinfo){}

Socket:: ~Socket ()
{
	close(m_socket);

}

const fd_t&  Socket::GetFD_t() const
{
	return m_socket;
}

ssize_t Socket::Send(std::tr1::shared_ptr<SocketStream> _stream)
{
	ssize_t count;
	count = send(m_socket, _stream->GetMessage(),  _stream->GetSize() , MSG_NOSIGNAL);
	if (0 > count)
	{
		if(errno == EAGAIN || errno == EWOULDBLOCK)
 		{
 		    throw Err_TryAgain("nonblocking mode. sending has failed");
 		}
 		else if( errno == EPIPE)
 		{
 		    throw Err_Disconnected("the connection has been closed");
 		}
 		else
 		{
     		throw std::runtime_error(strerror(errno));
 		}
	}
	return count;
}

std::tr1::shared_ptr<SocketStream> Socket::Recv()
{
	char buf[512];
	ssize_t count;
	
	count = recv(m_socket, buf, sizeof(buf)-1, 0);
 	if(count < 0)
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
 	else if(count == 0)
 	{ 		
 		throw Err_Disconnected("the connection has been closed");
 	}
	std::tr1::shared_ptr<SocketStream> stream(new SocketStream(buf, count));
	
	return stream;
}

Socket& Socket::operator<<(std::tr1::shared_ptr<SocketStream> _str)
{
	Send(_str);
	return *this;
}

Socket& Socket::operator>>(std::tr1::shared_ptr<SocketStream> _str)
{
	_str = Recv();
	return *this;
}


void Socket::SetNonBlocking()
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

const Peer_info& Socket::GetPeerInfo()const
{
    return m_info;
}

}
