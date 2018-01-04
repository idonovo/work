#ifndef __SOCKETMESSAGE_H__
#define __SOCKETMESSAGE_H__

#include <iostream>

#include <cstddef>

namespace Netcpp
{

class SocketStream
{

public:
	explicit SocketStream (void*, std::size_t _size);
	virtual ~SocketStream ();
	
	SocketStream(const SocketStream&);
	SocketStream& operator=(const SocketStream&);
	
	std::size_t GetSize()const;
	void* GetMessage()const;
	
private:

	void* m_message;
	std::size_t m_size;
};

std::ostream& operator<<(std::ostream& _os, const SocketStream&  _str);

}

#endif /* __SOCKETMESSAGE_H__ */

