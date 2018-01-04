#include "fd_t.h"

namespace Netcpp
{

fd_t::fd_t (){}

fd_t::fd_t (int _x): m_fd(_x){}

fd_t::fd_t::~fd_t (){}

fd_t::fd_t(const fd_t& _x)
{
	m_fd = _x.m_fd;
}

fd_t& fd_t::operator=(int x)
{
	m_fd = x;
		
	return *this;
}

fd_t& fd_t::operator=(const fd_t& _x)
{
	if(this != &_x)
	{
		m_fd = _x.m_fd;
	}
	
	return *this;
}
	
fd_t::operator int()
{
	return m_fd;
}

}

