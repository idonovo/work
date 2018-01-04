
#ifndef __ASCIIIO_H__
#define __ASCIIIO_H__


#include "virtIO_t.h"

class asciiIO_t: public virtIO_t
{

public:
    asciiIO_t(): virtIO_t(){}
	asciiIO_t(const string& _path, const string& _mode): virtIO_t(_path, _mode){}
	~asciiIO_t (){}
	
	virtual asciiIO_t& operator << (char _obj){return Write(_obj, "%c");}
	virtual asciiIO_t& operator << (short _obj){return Write(_obj, "%d");}
	virtual asciiIO_t& operator << (int _obj){return Write(_obj, "%d");}
	virtual asciiIO_t& operator << (long _obj){return Write(_obj, "%d");}
	virtual asciiIO_t& operator << (float _obj){return Write(_obj, "%f");}
	virtual asciiIO_t& operator << (unsigned char _obj){return Write(_obj, "%c");}
	virtual asciiIO_t& operator << (unsigned short _obj){return Write(_obj, "%d");}
	virtual asciiIO_t& operator << (unsigned int _obj){return Write(_obj, "%u");}
	virtual asciiIO_t& operator << (unsigned long _obj){return Write(_obj, "%ul");}
	virtual asciiIO_t& operator << (double _obj){return Write(_obj, "%uf");}
	
	
	virtual asciiIO_t& operator >> (char &_obj){return Read(_obj, "%c");}
	virtual asciiIO_t& operator >> (short &_obj){return Read(_obj, "%d");}
	virtual asciiIO_t& operator >> (int &_obj){return Read(_obj, "%d");}
	virtual asciiIO_t& operator >> (long &_obj){return Read(_obj, "%d");}
	virtual asciiIO_t& operator >> (float &_obj){return Read(_obj, "%f");}
	virtual asciiIO_t& operator >> (unsigned char &_obj){return Read(_obj, "%c");}
	virtual asciiIO_t& operator >> (unsigned short &_obj){return Read(_obj, "%d");}
	virtual asciiIO_t& operator >> (unsigned int &_obj){return Read(_obj, "%u");}
	virtual asciiIO_t& operator >> (unsigned long &_obj){return Read(_obj, "%ul");}
	virtual asciiIO_t& operator >> (double &_obj){return Read(_obj, "%uf");}  
	
private:
	asciiIO_t (const asciiIO_t& _asciiIO_t);
    asciiIO_t&operator=(const asciiIO_t& _asciiIO_t);
  
template<class T>
asciiIO_t& Write(T _t, char* _iden)
{
	
	if(m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	
	if(0 > fprintf(m_fp, _iden , _t))
	{
		throw writeErr_e;
	}	
	return *this; 
} 

template<class T>
asciiIO_t& Read(T& _t, char* _iden)
{
	if(m_mode[0] == 'w')
	{
		throw bad_access_e;
	}

	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	if(0 > fscanf(m_fp, _iden, &_t))
	{
		throw readErr_e;
	}
		
	return *this;  
}  
};
 

#endif /* __ASCIIIO_H__ */

