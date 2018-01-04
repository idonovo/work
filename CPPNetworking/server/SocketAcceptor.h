#ifndef __SERVERSOCKET_H__
#define __SERVERSOCKET_H__

#include "Peer_info.h"
#include "Socket.h"
#include "Selectable.h"


class SystemSocket;

namespace Netcpp
{
	
class SocketAcceptor: public Selectable
{
public:
	
	const static std::size_t DEF_SOCKET_QUEUE_SIZE = 1024;
	
	explicit SocketAcceptor (const Peer_info&);
	virtual ~SocketAcceptor();
	
	virtual bool Listen(std::size_t _size = DEF_SOCKET_QUEUE_SIZE);
	virtual std::tr1::shared_ptr<Socket>Accept();
	void SetNonBlocking();
	
private:	
	SocketAcceptor(const SocketAcceptor&);
	SocketAcceptor& operator=(const SocketAcceptor&);
	virtual const fd_t&  GetFD_t() const;
	
	void Bind(fd_t _socket, struct sockaddr_in* m_addr);
    void StartListening(fd_t _socket, std::size_t _size);
    void InitSocketAddr(struct sockaddr_in* m_addr, const Peer_info& _serverinfo);
    fd_t CreateChannel(void);
    
    fd_t m_socket;
	Peer_info m_info;
	bool m_isListening;
};

}


#endif /* __SERVERSOCKET_H__ */

