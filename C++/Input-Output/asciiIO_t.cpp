/*
#include "asciiIO_t.h"
#include <stdio.h>

asciiIO_t:: asciiIO_t(): virtIO_t(){}
 
asciiIO_t::asciiIO_t(const string& _path, const string& _mode): virtIO_t(_path, _mode){}

asciiIO_t::~asciiIO_t (){}


asciiIO_t& asciiIO_t::operator << (char _obj)
{
	if(m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	
	if(0 > fprintf(m_fp, "%c", _obj))
	{
		throw writeErr_e;
	}
		
	return *this; 
}

asciiIO_t& asciiIO_t::operator << (short _obj)
{
	if(m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	
	if(0 > fprintf(m_fp, "%d", _obj))
	{
		throw writeErr_e;
	}
		
	return *this; 
}

asciiIO_t& asciiIO_t::operator << (int _obj)
{
	if(m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	
	if(0 > fprintf(m_fp, "%d", _obj))
	{
		throw writeErr_e;
	}
		
	return *this; 
}

asciiIO_t& asciiIO_t::operator << (long _obj)
{
	if(m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	
	if(0 > fprintf(m_fp, "%d", _obj))
	{
		throw writeErr_e;
	}
		
	return *this; 
}

asciiIO_t& asciiIO_t::operator << (float _obj)
{
	if(m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	
	if(0 > fprintf(m_fp, "%f", _obj))
	{
		throw writeErr_e;
	}
		
	return *this; 
}

asciiIO_t& asciiIO_t::operator << (unsigned char _obj)
{
	if(m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	
	if(0 > fprintf(m_fp, "%c", _obj))
	{
		throw writeErr_e;
	}
		
	return *this; 
}

asciiIO_t& asciiIO_t::operator << (unsigned short _obj)
{
	if(m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	
	if(0 > fprintf(m_fp, "%d", _obj))
	{
		throw writeErr_e;
	}
		
	return *this; 
}

asciiIO_t& asciiIO_t::operator << (unsigned int _obj)
{
	if(m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	
	if(0 > fprintf(m_fp, "%u", _obj))
	{
		throw writeErr_e;
	}
		
	return *this; 
}

asciiIO_t& asciiIO_t::operator << (unsigned long  _obj)
{
	if(m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	
	if(0 > fprintf(m_fp, "%lu", _obj))
	{
		throw writeErr_e;
	}
		
	return *this; 
}

asciiIO_t& asciiIO_t::operator << (double _obj)
{
	if(m_mode[0] == 'r')
	{
		throw bad_access_e;
	}
	
	if(0 > fprintf(m_fp, "%lf", _obj))
	{
		throw writeErr_e;
	}
		
	return *this; 
}	

asciiIO_t& asciiIO_t::operator >> (char &_obj)
{
	if(m_mode[0] == 'w')
	{
		throw bad_access_e;
	}

	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	if(0 > fscanf(m_fp, "%c", &_obj))
	{
		throw readErr_e;
	}
		
	return *this; 
}

asciiIO_t& asciiIO_t::operator >> (short &_obj)
{
	if(m_mode[0] == 'w')
	{
		throw bad_access_e;
	}
	
	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	if(0 > fscanf(m_fp, "%d", &_obj))
	{
		throw readErr_e;
	}
		
	return *this; 
}

asciiIO_t& asciiIO_t::operator >> (int &_obj)
{
	if(m_mode[0] == 'w')
	{
		throw bad_access_e;
	}
	
	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	if(0 > fscanf(m_fp, "%d", &_obj))
	{
		throw readErr_e;
	}
		
	return *this; 
}

asciiIO_t& asciiIO_t::operator >> (long &_obj)
{
	if(m_mode[0] == 'w')
	{
		throw bad_access_e;
	}
	
	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	if(0 > fscanf(m_fp, "%d", &_obj))
	{
		throw readErr_e;
	}
		
	return *this; 
}

asciiIO_t& asciiIO_t::operator >> (float &_obj)
{
	if(m_mode[0] == 'w')
	{
		throw bad_access_e;
	}
	
	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	if(0 > fscanf(m_fp, "%f", &_obj))
	{
		throw readErr_e;
	}
		
	return *this; 
}

asciiIO_t& asciiIO_t::operator >> (unsigned char &_obj)
{
	if(m_mode[0] == 'w')
	{
		throw bad_access_e;
	}
	
	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	if(0 > fscanf(m_fp, "%c", &_obj))
	{
		throw readErr_e;
	}
		
	return *this; 
}

asciiIO_t& asciiIO_t::operator >> (unsigned short &_obj)
{
	if(m_mode[0] == 'w')
	{
		throw bad_access_e;
	}
	
	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	if(0 > fscanf(m_fp, "%d", &_obj))
	{
		throw readErr_e;
	}
		
	return *this; 
}

asciiIO_t& asciiIO_t::operator >> (unsigned int &_obj)
{
	if(m_mode[0] == 'w')
	{
		throw bad_access_e;
	}
	
	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	if(0 > fscanf(m_fp, "%u", &_obj))
	{
		throw readErr_e;
	}
		
	return *this; 
}

asciiIO_t& asciiIO_t::operator >> (unsigned long  &_obj)
{
	if(m_mode[0] == 'w')
	{
		throw bad_access_e;
	}
	
	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	if(0 > fscanf(m_fp, "%lu", &_obj))
	{
		throw readErr_e;
	}
		
	return *this; 
}

asciiIO_t& asciiIO_t::operator >> (double &_obj)
{
	if(m_mode[0] == 'w')
	{
		throw bad_access_e;
	}
	
	if(feof(m_fp))
	{
		throw bad_access_e;
	}
	
	if(0 > fscanf(m_fp, "%lf", &_obj))
	{
		throw readErr_e;
	}
		
	return *this; 
}	

*/

 



