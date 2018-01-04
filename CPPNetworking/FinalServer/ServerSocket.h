#ifndef __MYSERVERSOCKET_H__
#define __MYSERVERSOCKET_H__

#include "Socket_t.h"
#include "Peer_info.h"
#include "Peer_info.h"

#include <cstddef>
#include <tr1/memory>

namespace Netcpp
{

class ServerSocket: public Socket_t
{
public:
	const std::size_t DEF_SOCKET_QUEUE_SIZE = 1024;	
	
	ServerSocket();
	explicit ServerSocket(int, const Peer_info&, std::size_t _size);
	explicit ServerSocket(const Peer_info& _info, std::size_t _size);
	
	virtual ~ServerSocket();
	
	void SetPeer_info(const Peer_info&);
	void SetQueSize(std::size_t);
	
	void ListenToNewPeerinfo(const Peer_info&);
	
	bool ServerSocket::AcceptNewSocket(std::tr1::shared_ptr<Socket_t>)
	std::tr1::shared_ptr<Socket_t> AcceptNewSocket(BlokingMode);

private:
	ServerSocket(const ServerSocket&);
	ServerSocket operator= (const ServerSocket&);
	
	void InitServerSocket(std::size_t _size);
	void StartListening(std::size_t _size);
	void InitSocketAddr(struct sockaddr_in* m_addr, const Peer_info& _serverinfo);
	void Bind(struct sockaddr_in* m_addr);
	
private:
	Peer_info m_info;
	std::size_t m_queueSize;
};

}



#endif /* __MYSERVERSOCKET_H__ */

