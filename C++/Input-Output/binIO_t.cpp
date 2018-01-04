#include "binIO_t.h"
#include "string.h"

    
/*   
binIO_t::binIO_t(): virtIO_t(){}

binIO_t:: binIO_t(const string& _path, const string& _mode): virtIO_t(_path, _mode){}

binIO_t:: ~binIO_t() {}
   
binIO_t& binIO_t::operator << (char _obj)
{
	if(m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	
	if(1 != fwrite(&_obj,sizeof(char), 1, m_fp))
	{
		throw writeErr_e;
	}
		
	return *this; 
}


binIO_t& binIO_t::operator << (short _obj)
{
	if(m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	
	if(1 != fwrite(&_obj ,sizeof(short), 1, m_fp))
	{
		throw writeErr_e;
	}
		
	return *this; 
}

binIO_t& binIO_t::operator << (int _obj)
{
	if(m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	
	if(1 != fwrite(&_obj ,sizeof(int), 1, m_fp))
	{
		throw writeErr_e;
	}
		
	return *this; 
}

binIO_t& binIO_t::operator << (long _obj)
{
	if(m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	
	if(1 != fwrite(&_obj ,sizeof(long), 1, m_fp))
	{
		throw writeErr_e;
	}
		
	return *this; 
}

binIO_t& binIO_t::operator << (float _obj)
{
	if(m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	
	if(1 != fwrite(&_obj ,sizeof(float), 1, m_fp))
	{
		throw writeErr_e;
	}
		
	return *this; 
}

binIO_t& binIO_t::operator << (unsigned char _obj)
{
	if(m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	
	if(1 != fwrite(&_obj ,sizeof(unsigned char), 1, m_fp))
	{
		throw writeErr_e;
	}
		
	return *this; 
}

binIO_t& binIO_t::operator << (unsigned short _obj)
{
	if(m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	
	if(1 != fwrite(&_obj ,sizeof(unsigned short), 1, m_fp))
	{
		throw writeErr_e;
	}
		
	return *this; 
}

binIO_t& binIO_t::operator << (unsigned int _obj)
{
	if(m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	
	if(1 != fwrite(&_obj ,sizeof(unsigned int), 1, m_fp))
	{
		throw writeErr_e;
	}
		
	return *this; 
}

binIO_t& binIO_t::operator << (unsigned long  _obj)
{
	if(m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	
	if(1 != fwrite(&_obj ,sizeof(unsigned long), 1, m_fp))
	{
		throw writeErr_e;
	}
		
	return *this; 
}

binIO_t& binIO_t::operator << (double _obj)
{
	if(m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	
	if(1 != fwrite(&_obj ,sizeof(double), 1, m_fp))
	{
		throw writeErr_e;
	}
		
	return *this; 
}	

binIO_t& binIO_t::operator >> (char &_obj)
{
	if(m_mode[0] == 'w')
	{
		throw bad_access_e;
	}
	
	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	if(1 != fread(&_obj ,sizeof(char), 1, m_fp))
	{
		throw readErr_e;
	}
		
	return *this; 
}

binIO_t& binIO_t::operator >> (short &_obj)
{
	if(m_mode[0] == 'w')
	{
		throw bad_access_e;
	}
	
	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	if(1 != fread(&_obj ,sizeof(short), 1, m_fp))
	{
		throw readErr_e;
	}
		
	return *this; 
}

binIO_t& binIO_t::operator >> (int &_obj)
{
	if(m_mode[0] == 'w')
	{
		throw bad_access_e;
	}
	
	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	if(1 != fread(&_obj ,sizeof(int), 1, m_fp))
	{
		throw readErr_e;
	}
		
	return *this; 
}

binIO_t& binIO_t::operator >> (long &_obj)
{
	if(m_mode[0] == 'w')
	{
		throw bad_access_e;
	}
	
	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	if(1 != fread(&_obj ,sizeof(long), 1, m_fp))
	{
		throw readErr_e;
	}
		
	return *this; 
}

binIO_t& binIO_t::operator >> (float &_obj)
{
	if(m_mode[0] == 'w')
	{
		throw bad_access_e;
	}
	
	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	if(1 != fread(&_obj ,sizeof(float), 1, m_fp))
	{
		throw readErr_e;
	}
		
	return *this; 
}

binIO_t& binIO_t::operator >> (unsigned char &_obj)
{
	if(m_mode[0] == 'w')
	{
		throw bad_access_e;
	}
	
	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	if(1 != fread(&_obj ,sizeof(unsigned char), 1, m_fp))
	{
		throw readErr_e;
	}
		
	return *this; 
}

binIO_t& binIO_t::operator >> (unsigned short &_obj)
{
	if(m_mode[0] == 'w')
	{
		throw bad_access_e;
	}
	
	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	if(1 != fread(&_obj ,sizeof(unsigned short), 1, m_fp))
	{
		throw readErr_e;
	}
		
	return *this; 
}

binIO_t& binIO_t::operator >> (unsigned int &_obj)
{
	if(m_mode[0] == 'w')
	{
		throw bad_access_e;
	}
	
	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	if(1 != fread(&_obj ,sizeof(unsigned int), 1, m_fp))
	{
		throw readErr_e;
	}
		
	return *this; 
}

binIO_t& binIO_t::operator >> (unsigned long  &_obj)
{
	if(m_mode[0] == 'w')
	{
		throw bad_access_e;
	}
	
	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	if(1 != fread(&_obj ,sizeof(unsigned long), 1, m_fp))
	{
		throw readErr_e;
	}
		
	return *this; 
}

binIO_t& binIO_t::operator >> (double &_obj)
{
	if(m_mode[0] == 'w')
	{
		throw bad_access_e;
	}
	
	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	if(1 != fread(&_obj ,sizeof(double), 1, m_fp))
	{
		throw readErr_e;
	}
		
	return *this; 
}	

binIO_t& binIO_t::operator>>(void* _buf)
{
	if(!_buf && m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	m_buf = _buf;
	m_readWriteMode = true;
	return *this; 
}

binIO_t& binIO_t::operator<<(const void* _buf)
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

void  binIO_t::operator,(unsigned int _len)
{
	if(m_readWriteMode)
	{
		if(_len == fwrite(m_buf ,sizeof(char), _len , m_fp))
		{
			throw writeErr_e;
		}
	}
	
	if(_len == fread(m_buf ,sizeof(char), _len , m_fp))
	{
		throw readErr_e;
	}
}	
 
*/	
