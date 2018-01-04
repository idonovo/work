#include "virtIO_t.h"
#include "string.h"


virtIO_t::virtIO_t()
{
	m_fp = 0;
}


virtIO_t::virtIO_t (const string& _path, const string& _mode)
{
	if(CheckMode(_mode))
	{
		m_path = _path;
		char path[32];
		strcpy(path,_path.c_str());
		m_fp = fopen(path, m_mode);
			
		if(!m_fp)
		{
			throw cant_open_file_e;
		}
	}
}
	
virtIO_t::~virtIO_t ()
{
	fclose(m_fp);
}

bool virtIO_t::Open(const string& _path, const string& _mode)
{
	return (CheckMode(_mode) && SetPath(_path))? true: false;
}

void virtIO_t::Close()
{
	if(m_fp)
	{
		fclose(m_fp);
	}
}

bool virtIO_t::SetPath(const string& _path)
{
	m_path = _path;
	fclose(m_fp);
	char path[32];
	strcpy(path, _path.c_str());
	m_fp = fopen(path, m_mode);
	return (m_fp)? true: false;
}

bool virtIO_t::SetMode(const string& _mode)
{
	if(CheckMode(_mode))
	{
		char path[32];
		strcpy(path, m_path.c_str());
		m_fp = fopen(path, m_mode);
		return true;
	}
	return false;
}

bool virtIO_t::CheckMode(const string& _mode)
{
	
	if(0 == _mode.compare("r"))
	{
		m_mode[0] = 'r';
		return 1;
	}
	
	if(0 == _mode.compare("w"))
	{
		m_mode[0] = 'w';
		return 1;
	}
	
	if(0 == _mode.compare("a"))
	{
		m_mode[0] = 'a';
		return 1;
	}
	
	if(0 == _mode.compare("r+"))
	{
		strcpy(m_mode, "r+");
		return 1;
	}
	
	if(0 == _mode.compare("w+"))
	{
		strcpy(m_mode, "w+");
		return 1;
	}
	
	if(0 == _mode.compare("a+"))
	{
		strcpy(m_mode, "a+");
		return 1;
	}
	return 0;
}

long int virtIO_t::Length() const
{
	if(m_fp)
	{
		FILE* temp = m_fp;
		fseek(temp, 0, SEEK_END); 
		long int length=ftell(temp);
		return length;
	}
	return 0;
}


