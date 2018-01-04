#ifndef __NETWORKERR_H__
#define __NETWORKERR_H__

#include <stdexcept>
#include <string>

namespace Netcpp
{
	
class Err_Disconnected : public std::runtime_error
{
public:
	explicit Err_Disconnected(const std::string& _what)
	: std::runtime_error(_what), whatMsg(_what)
	{
		
	}
	
	virtual ~Err_Disconnected() throw () 
	{
		
	}
	
	virtual const char* what() const throw()
	{
		return whatMsg.c_str();
	}

private:
	std::string whatMsg;
};

class Err_TryAgain : public std::runtime_error
{
public:
	explicit Err_TryAgain(const std::string& _what)
	: std::runtime_error(_what), whatMsg(_what)
	{
		
	}
	
	virtual ~Err_TryAgain() throw () 
	{
		
	}
	
	virtual const char* what() const throw()
	{
		return whatMsg.c_str();
	}

private:
	std::string whatMsg;
};
	
} //namespace Networking

#endif /* __NETWORKERR_H__ */

