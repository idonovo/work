#ifndef __StringCPP_H__
#define __StringCPP_H__

#include <stddef.h>
#include <stdio.h>
#include <iostream>
using namespace std;

class String_t
{

	public: 
	String_t();
	~String_t();
	String_t(const char* _str);
	String_t(const String_t& _origin);
	
	const String_t& operator=(const String_t& _origin);
	const String_t& operator+=(const String_t& _toAdd);
	int operator==(const String_t& _str)const{return compare(_str) == 0 ? 1: 0;}
	int operator!=(const String_t& _str)const{return compare(_str) != 0 ? 1: 0;}
	int operator<=(const String_t& _str)const{return compare(_str) == 1 || compare(_str) == 0 ? 1: 0;}
	int operator>=(const String_t& _str)const{return compare(_str) == 2 ||  compare(_str) == 0 ? 1: 0;}
	int operator>(const String_t& _str)const{return compare(_str) != 1 ? 1: 0;}
	int operator<(const String_t& _str)const{return compare(_str) != 2 ? 1: 0;}
	char operator[](size_t _index)const{return m_length < _index? '\0': string[_index-1];}
	String_t operator()(unsigned int _start, unsigned int _len) const;
	
	
	size_t 	    	length() const{return m_length;};
	void 	    	setString(const char* _str);
	const char*		getString() const{return string;};
	int 	    	compare(const String_t& _origin) const;
	void	        print() const;
	void        	ConvertToUpper();
	void        	ConvertToLower();
	const char* 	Prepend(const char* _str);
	const String_t& Prepend(const String_t& _str);
	int         	Contains(const char* _str) const;
	size_t			GetFirst(char _x)const;
	size_t			GetLast(char _x)const;
	
	static size_t   GetNumOfObjs(){return m_numOfStrings;}
	static size_t 	GetDefaultSize(){return m_defaultCapacity;}
	static size_t	SetDefaultSize(size_t _size){size_t temp = m_defaultCapacity; 
												while(_size > m_defaultCapacity)
												{
													m_defaultCapacity *= 2;
												}
												return temp;}
	static bool		GetCaseSens(){return m_caseSens;}
	static void 	SetOnCaseSens(){m_caseSens = true;}
	static void 	SetOffCaseSens(){m_caseSens = false;}

	private:
	static	size_t 	m_defaultCapacity;
	static 	size_t 	m_numOfStrings;
	static 	bool 	m_caseSens; 
	char*   		string;
	size_t  		m_length;
	size_t			m_capacity;
	
	inline void    	SetDefaultStr();
	void 			CreateFrom(const char* _str);
	void 			SetNewCapacity(size_t _x);
};

/***********************************************************/
ostream& operator<<(ostream& _os, const String_t& _string);

istream& operator>>(istream& _os, String_t& _string);

#endif /* __StringCPP_H__ */

