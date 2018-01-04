#ifndef __ISOCKET_H__
#define __ISOCKET_H__

#include "fd_t.h"
#include "SocketStream.h"
#include "Peer_info.h"
#include "Selectable.h"

#include <cstddef>
#include <tr1/memory>

namespace Netcpp
{


class Socket: public Selectable
{
public:
	
	static const std::size_t DEF_PORT = 1023;
	
	explicit Socket (fd_t , const Peer_info&);
	virtual ~Socket ();
	
	ssize_t Send(std::tr1::shared_ptr<SocketStream>);
	std::tr1::shared_ptr<SocketStream> Recv();
	void SetNonBlocking();
	const Peer_info& GetPeerInfo()const;
	
	Socket& operator<<(std::tr1::shared_ptr<SocketStream>);
	Socket& operator>>(std::tr1::shared_ptr<SocketStream>);	
	
private:
	virtual fd_t&  GetFD_t();

	fd_t m_socket;
	Peer_info m_info;
};


}

#endif /* __ISOCKET_H__ */

