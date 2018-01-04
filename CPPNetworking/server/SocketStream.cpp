#include "SocketStream.h"

namespace Netcpp
{

SocketStream::SocketStream (void* _obj, size_t _size): 
m_message(_obj), 
m_size(_size){}

SocketStream::~SocketStream (){}

SocketStream::SocketStream(const SocketStream& _msg)
{
	m_message = _msg.m_message;
}

SocketStream& SocketStream::operator=(const SocketStream& _msg)
{
	if(this != &_msg)
	{
		m_message = _msg.m_message;
	}
	return *this;
}

std::size_t SocketStream::GetSize()const
{
	return m_size;
}

void* SocketStream::GetMessage()const
{
	return  m_message;

}

std::ostream& operator<<(std::ostream& _os, const SocketStream&  _str)
{
	_os << "Message:" << _str.GetMessage();
	return _os;
}


}

