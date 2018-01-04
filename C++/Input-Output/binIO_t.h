#ifndef __BIN_H__
#define __BIN_H__

#include "virtIO_t.h"

#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

class binIO_t: public virtIO_t
{

public:
    binIO_t(): virtIO_t(){}
	binIO_t(const string& _path, const string& _mode): virtIO_t(_path, _mode){}
    ~binIO_t(){}
    
	virtual binIO_t& operator << (char _obj){return Write(_obj  ,1);}
	virtual binIO_t& operator << (short _obj){return Write(_obj  ,1);}
	virtual binIO_t& operator << (int _obj){return Write(_obj  ,1);}
	virtual binIO_t& operator << (long _obj){return Write(_obj  ,1);}
	virtual binIO_t& operator << (float _obj){return Write(_obj  ,1);}
	virtual binIO_t& operator << (unsigned char _obj){return Write(_obj  ,1);}
	virtual binIO_t& operator << (unsigned short _obj){return Write(_obj  ,1);}
	virtual binIO_t& operator << (unsigned int _obj){return Write(_obj  ,1);}
	virtual binIO_t& operator << (unsigned long _obj){return Write(_obj  ,1);}
	virtual binIO_t& operator << (double _obj){return Write(_obj  ,1);}
	

	virtual binIO_t& operator>>(void* _buf)
	{
		if(!_buf && m_mode[0] == 'r')
		{
			throw bad_access_e;
		}
		m_buf = _buf;
		m_readWriteMode = true;
		return *this; 
	}
	
    virtual binIO_t& operator<<(const void* _buf)
    {
		if(!_buf && m_mode[0] == 'w')
		{
			throw bad_access_e;
		}
	
		if(feof(m_fp))
		{
			throw bad_access_e;
		}
	
		m_buf = (void*)_buf;
		m_readWriteMode = false;
		return *this; 
    }

	virtual void  operator,(unsigned int len)
	{
		(m_readWriteMode)? Write(m_buf, len) : Read(m_buf, len); 
	}
	
	virtual binIO_t& operator >> (char &_obj){return Read(_obj  ,sizeof(char));}
	virtual binIO_t& operator >> (short &_obj){return Read(_obj  ,sizeof(short));}
	virtual binIO_t& operator >> (int &_obj){return Read(_obj ,sizeof(int));}
	virtual binIO_t& operator >> (long &_obj){return Read(_obj  ,sizeof(long));}
	virtual binIO_t& operator >> (float &_obj){return Read(_obj  ,sizeof(float));}
	virtual binIO_t& operator >> (unsigned char &_obj){return Read(_obj  ,sizeof(unsigned char));}
	virtual binIO_t& operator >> (unsigned short &_obj){return Read(_obj  ,sizeof(unsigned short));}
	virtual binIO_t& operator >> (unsigned int &_obj){return Read(_obj  ,sizeof(unsigned int));}
	virtual binIO_t& operator >> (unsigned long &_obj){return Read(_obj  ,sizeof(unsigned long));}
	virtual binIO_t& operator >> (double &_obj){return Read(_obj  ,sizeof(double));}
	
private:
	binIO_t (const binIO_t& _binIO_t);
    binIO_t&operator=(const binIO_t& _binIO_t);

private:

	void* m_buf;
	bool  m_readWriteMode;
	
template<class T>
binIO_t& Write(T _t, size_t _len)
{
	
	if(m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	
	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	fwrite(&_t ,_len, 1, m_fp);
	
	return *this; 
} 

template<class T>
binIO_t& Read(T& _t, size_t _len)
{
	if(m_mode[0] == 'w')
	{
		throw bad_access_e;
	}
	
	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	fread(&_t ,_len, 1, m_fp);
	
	return *this;  
}
 	
};

#endif /* __BIN_H__ */

