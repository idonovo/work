#ifndef __MYSOCKET_T_H__
#define __MYSOCKET_T_H__

#include "fd_t.h"

namespace Netcpp
{

enum BlokingMode
{
	Bloking,
	Non_blocking
};

class Socket_t
{
public:
	friend class SocketNotifier;
	explicit Socket_t();
	explicit Socket_t (const fd_t& _fd);
	explicit Socket_t (int _fd);
	
	virtual ~Socket_t ();

protected:
	void SetBlockingMode(BlokingMode _mode);
	mutable fd_t m_fd;
	
private:
	Socket_t& operator=(const Socket_t&);
	Socket_t (const Socket_t&);
	void InitSocket();
	
private:
	const fd_t& GetFd_t() const;
	BlokingMode m_mode;
};

}

#endif /* __MYSOCKET_T_H__ */

