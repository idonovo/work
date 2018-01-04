#ifndef __MYFDT_H__
#define __MYFDT_H__

namespace Netcpp
{

class fd_t
{
public:
	explicit fd_t ();
	explicit fd_t (int);
	virtual ~fd_t ();
	fd_t(const fd_t&);
	
	fd_t& operator=(int);
	fd_t& operator=(const fd_t&);
	
	operator int();

private:
	int m_fd;
};

}

#endif /* __MYFDT_H__ */

