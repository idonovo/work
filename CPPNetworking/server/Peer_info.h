#ifndef __HOSTINFO_H__
#define __HOSTINFO_H__

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include "fd_t.h"

namespace Netcpp
{

struct Peer_info
{
	Peer_info (int _port, const std::string& _ip);
	virtual ~Peer_info (){};
	
	Peer_info(const struct sockaddr_in&);
	Peer_info& operator=(const Peer_info&);
	Peer_info& operator=(const struct sockaddr_in&);
	
	bool operator ==(const Peer_info&) const; 
	
	
	std::string GetIP() const {return m_ip;}
	int GetPort() const {return  m_port;}

	void ResolvePeerName(std::string& _str);
	
	int m_port;
	std::string m_ip;
};

inline Peer_info::Peer_info (int _port, const std::string& _ip):m_port(_port),m_ip(_ip)
{
	
	ResolvePeerName(m_ip);
}  

inline void Peer_info::ResolvePeerName(std::string& _str)
{
	struct addrinfo *res;
	int result = getaddrinfo (_str.c_str(), NULL, NULL, &res);
	if(result == 0)
	{
		std::string newStr(inet_ntoa(((struct sockaddr_in *) res->ai_addr)->sin_addr));
		_str = newStr;
	}
}

inline Peer_info::Peer_info(const struct sockaddr_in& _add)
{
    m_ip = inet_ntoa(_add.sin_addr);
    m_port = ntohs(_add.sin_port);
}

inline Peer_info& Peer_info::operator=(const Peer_info& _info)
{
    if(this != & _info)
    {
        m_ip = _info.m_ip;
        m_port = _info.m_port;
    }
    return *this;
}

inline Peer_info& Peer_info::operator=(const struct sockaddr_in& _add)
{
    m_ip = inet_ntoa(_add.sin_addr);
    m_port = ntohs(_add.sin_port);
    return *this;
}

inline bool Peer_info::operator ==(const Peer_info& _peer) const
{
	return (m_ip == _peer.m_ip && m_port == _peer.m_port);
} 

}


#endif /* __HOSTINFO_H__ */

