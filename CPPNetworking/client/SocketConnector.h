#ifndef __CLIENTSOCKET_H__
#define __CLIENTSOCKET_H__

#include "Peer_info.h"
#include <tr1/memory>


namespace Netcpp
{

class Socket;

class SocketConnector
{

public:
	explicit SocketConnector();
	virtual ~SocketConnector ();
	virtual std::tr1::shared_ptr<Socket> Connect(const Peer_info&);
	
private:	
	SocketConnector(const SocketConnector&);
	SocketConnector& operator=(const SocketConnector&);
	
	void InitSocketAddr(struct sockaddr_in* m_addr, const Peer_info& _serverinfo);
    fd_t CreateChannel(void);
};	
	


}
#endif /* __CLIENTSOCKET_H__ */

