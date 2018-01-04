#ifndef __MY_ANOTHERSTRING_H__
#define __MY_ANOTHERSTRING_H__

#include <cstddef>
#include "myBuffer.h"
//namespace advcpp
//{

class String_t
{

public:
	String_t (const char* = "");
	String_t (const String_t& _string);
	virtual ~String_t ();
    String_t&operator=(const String_t& _string);
    String_t&operator=(const char*);
    
    bool operator== (const String_t& _string) const;
    bool operator== (const char*) const;
    bool operator!= (const String_t& _string) const; 
    bool operator!= (const char*) const; 
    
    const char& operator[] (std::size_t _pos)const;
   	char&		operator[] (std::size_t _pos); 
   	String_t operator+(const String_t& _string)const;
   	String_t operator+(const char*)const;  
    
    const char* Get_C_Str()const;
    
    void ToUpper();
    void ToLower();
    
    std::size_t Length()const;
    
private:
	Buffer_t<char>	m_buffer;
	std::size_t m_length;
};

//} // namespace
#endif /* __MY_STRING_H__ */

