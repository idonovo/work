#ifndef __MY_ANOTHERSTRING_H__
#define __MY_ANOTHERSTRING_H__

#include <cwchar>
#include <cstddef>
#include <iostream>
#include "StringMan.h"

#include "myBuffer.h"
namespace advcpp
{

template <class T>
class String_t
{

public:
	String_t ();
	String_t (const T*);
	String_t (const String_t& _string);
	virtual ~String_t ();
    String_t&operator=(const String_t& _string);
    String_t&operator=(const T*);
    
    bool operator== (const String_t& _string) const;
    bool operator== (const T*) const;
    bool operator!= (const String_t& _string) const; 
    bool operator!= (const T*) const; 
    
    const T& operator[] (std::size_t _pos)const;
   	T&		operator[] (std::size_t _pos); 
   	String_t operator+(const String_t& _string)const;
   	String_t operator+(const T*)const;  
    
    const T* c_str()const;
    
    std::size_t Length()const;
    
private:
	Buffer_t<T>	m_buffer;
	std::size_t m_length;
};

//std::ostream& operator<<(std::ostream& _os, const String_t& _string);

//std::istream& operator>>(std::istream& _os, const String_t& _string);


std::ostream& operator<<(std::ostream& _os, const String_t<char>& _string)
{
	_os<< _string.c_str();
	return _os;
}


std::ostream& operator<<(std::ostream& _os, const String_t<wchar_t>& _string)
{
	_os<< _string.c_str();
	return _os;
}


//template <class T>
//std::istream& operator>>(std::istream& _os,String_t<T>& _string)
//{
//	char buffer[128];
////	_os >> buffer;
////	_string.setString((const char*)buffer);
//	return _os;
//} 

template <class T>
String_t<T>::String_t()
{
	m_length = 1;
} 

template <class T>
String_t<T>::String_t(const T* _str) 
{
	
	if(!_str)
	{
		throw std::invalid_argument("null_ptr");
	} 
	
	m_length = Str_len(_str) + 1;
	m_buffer.SetElement(_str, m_length); 
}

template <class T>
String_t<T>::String_t:: ~String_t(){}


template <class T>
String_t<T>::String_t (const String_t& _string)
{
	m_buffer = _string.m_buffer;
	m_length = _string.m_length;
}

template <class T>
String_t<T>& String_t<T>::operator=(const String_t& _string)
{
	if(this != &_string)
	{
		m_buffer = _string.m_buffer;
		m_length = _string.m_length;
	}
	return *this;
}

template <class T>
String_t<T>& String_t<T>::operator=(const T* _str)
{
    if(!_str)
	{
		throw std::invalid_argument("null_ptr");
	} 
	m_length = Str_len(_str)+1; 
    m_buffer.SetElement(_str, m_length); 
    return *this;
}

template <class T>
bool String_t<T>::operator== (const T* _str) const
{
    return (0 == Str_cmp(m_buffer.GetBuffer(), _str));
}

template <class T>
bool String_t<T>::operator!= (const T* _str) const
{
    return (0 != Str_cmp(m_buffer.GetBuffer(), _str));
}

template <class T>
bool String_t<T>::operator== (const String_t& _string) const
{
	return (0 == Str_cmp(m_buffer.GetBuffer(), _string.m_buffer.GetBuffer()));
}

template <class T>
bool String_t<T>::operator!= (const String_t& _string) const
{
	return (0 != Str_cmp(m_buffer.GetBuffer(), _string.m_buffer.GetBuffer()));
}

template <class T>
String_t<T> String_t<T>:: operator+(const String_t& _string)const
{
	String_t temp;
	temp.m_buffer = m_buffer + _string.m_buffer;
	return temp;
}

template <class T>
String_t<T> String_t<T>::operator+(const T* _str)const
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

template <class T>
const T* String_t<T>::String_t::c_str()const
{
	return m_buffer.GetBuffer();
}

template <class T>
const T& String_t<T>::operator[] (std::size_t  _pos)const
{
	return m_buffer[_pos];
}

template <class T>
T& String_t<T>::operator[] (std::size_t _pos)
{
	return m_buffer[_pos];
} 

template <class T>
std::size_t String_t<T>::Length() const
{
	return m_length-1;
}

//template <class T>
//std::ostream& operator<<(std::ostream& _os, const String_t& _string)
//{
//	_os<< c_str();
//	return _os;
//}

} // namespace
#endif /* __MY_STRING_H__ */

