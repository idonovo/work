#include "myString.h"
#include "myBuffer.h"

#include <string.h>
#include <stdio.h>
#include <ctype.h>
//namespace advcpp
//{


String_t::String_t(const char* _str) 
{
	
	if(!_str)
	{
		throw std::invalid_argument("null_ptr");
	} 
	m_length = strlen(_str);
	m_buffer.SetElement(_str, m_length); 
}

String_t:: ~String_t(){}

String_t::String_t (const String_t& _string)
{
	m_buffer = _string.m_buffer;
	m_length = _string.m_length;
}

String_t& String_t::operator=(const String_t& _string)
{
	if(this != &_string)
	{
		m_buffer = _string.m_buffer;
		m_length = _string.m_length;
	}
	return *this;
}

String_t& String_t::operator=(const char* _str)
{
    if(!_str)
	{
		throw std::invalid_argument("null_ptr");
	} 
	m_length = strlen(_str); 
    m_buffer.SetElement(_str, m_length); 
    return *this;
}


bool String_t::operator== (const char* _str) const
{
    return (0 == strcmp(m_buffer.GetBuffer(), _str));
}
bool String_t::operator!= (const char* _str) const
{
    return (0 ==(*this == _str));
}

bool String_t::operator== (const String_t& _string) const
{
	return *this == _string.m_buffer.GetBuffer();
}

bool String_t::operator!= (const String_t& _string) const
{
	return (0 == (*this == _string.m_buffer.GetBuffer()));
}

String_t String_t::operator+(const String_t& _string)const
{
	String_t temp;
	temp.m_buffer = m_buffer + _string.m_buffer;
	return temp;
}

String_t String_t::operator+(const char* _str)const
{
	if(!_str)
	{
		throw std::invalid_argument("null_ptr");
	} 
	String_t temp1(_str);
	String_t temp2(*this);
	temp2.m_buffer += temp1.m_buffer;
	return temp2;
}  

const char* String_t::String_t::Get_C_Str()const
{
	return m_buffer.GetBuffer();
}

const char& String_t::operator[] (std::size_t  _pos)const
{
	return m_buffer[_pos];
}

char& String_t::operator[] (std::size_t _pos)
{
	return m_buffer[_pos];
} 

std::size_t  String_t::Length() const
{
	return m_length;
}

void String_t::ToUpper()
{
	
	for (unsigned int i = 0; i < m_length; i++)
	{
		m_buffer[i] = static_cast<char>(toupper(m_buffer[i]));
	}

} 

void String_t::ToLower()
{
   	for (unsigned int i = 0; i < m_length; i++)
	{
		m_buffer[i] = static_cast<char>(tolower(m_buffer[i]));
	}
} 

//} //namespace

