
#include "string_t.h"
#include <ctype.h>
#include <string.h>

#define DEFAULT_SIZE 16

size_t  String_t::m_defaultCapacity = DEFAULT_SIZE;
bool 	String_t::m_caseSens = true;
size_t 	String_t::m_numOfStrings = 0;

/*******************Global Funcs***********************************/
ostream& operator<<(ostream& _os, const String_t& _string)
{
	_os<< _string.getString();
	return _os;
}

istream& operator>>(istream& _os, String_t& _string)
{
	char buffer[128];
	_os >> buffer;
	_string.setString((const char*)buffer);
	return _os;
} 
/*******************Private Funcs***********************************/
void String_t::SetDefaultStr()
{
    m_capacity = m_defaultCapacity;
    string =  new char[m_capacity];
	if(!string){/*TODO*/ }
    string[0] = '\0';
    m_length = 1;
}

void String_t::SetNewCapacity(size_t _x)
{
    while(_x > m_capacity)
    {
    	m_capacity *= 2;
    }
}

void String_t::CreateFrom(const char* _str)
{

   	if(!_str)
   	{
   		SetDefaultStr();
   		return;
   	}
   	else
   	{
   		if((m_length = strlen(_str)) > m_capacity)
   		{
   			SetNewCapacity(m_length);
   			delete string;
   			string =  new char[m_capacity];
			if(!string){/*TODO*/ }
   		}
		strcpy(string, _str);
   	}
}
/*******************Public Funcs***********************************/
String_t:: String_t()
{
	SetDefaultStr();
	++m_numOfStrings;
}

String_t:: String_t(const char* _str)
{
	m_capacity = 2;
	CreateFrom(_str);
	++m_numOfStrings;
}

String_t:: String_t(const String_t& _origin)
{
	m_capacity = 2;
	CreateFrom(_origin.getString());
	++m_numOfStrings;
}

String_t:: ~String_t()
{
	delete[] string;
	--m_numOfStrings;
}


void String_t:: setString(const char* _str)
{
	CreateFrom(_str);
}

int String_t::compare(const String_t& _origin) const
{
	int res;
	
	if(m_caseSens == true)
	{
		res = strcmp(string, _origin.string);
	}
	else
	{
		res = strcasecmp(string, _origin.string);
	}
	
	return res == 0 ? 0 : (res > 0 ? 2 : 1 ); 
}

void String_t::ConvertToUpper()
{
   size_t i = 0; 
   
   while(string[i])
   {
     string[i]= (char)(toupper(string[i]));
     i++;
   }

} 

void String_t::ConvertToLower()
{
   size_t i = 0; 
   
   while(string[i])
   {
     string[i]= (char)(tolower(string[i]));
     i++;
   }
} 

const char* String_t::Prepend(const char* _str)
{
    
    if(_str)
    {
		if((m_length += strlen(_str)) > m_capacity)
		{
			SetNewCapacity(m_length);
		}
		char* newString = new char[m_capacity];
		strcpy(newString, _str);
		strcat(newString, string);
		delete string;
		string = newString;
    }
    return string;
}

const String_t& String_t::Prepend(const String_t& _toAdd)
{
	
	if((m_length += _toAdd.length()) > m_capacity)
	{
		SetNewCapacity(m_length);
	}
	
	char* newString = new char[m_capacity];
	strcpy(newString, _toAdd.getString());
	strcat(newString, string);
	delete string;
	string = newString;
  
    return *this;
}

int String_t::Contains(const char* _str) const
{
    if(!_str)
    {
        return -1;
    } 
    
    if(m_caseSens == true)
	{
		return (strstr(string, _str))? 1: 0;
	}
	return (strcasestr(string, _str))? 1: 0;
}

size_t String_t:: GetFirst(char _x)const
{
	size_t i = 0;
	if(m_caseSens == true)
	{
		while(string[i])
		{
			if(string[i] == _x)
			{
				return i+1;
			}
			++i;
		}
		return 0;
	}
	else
	{
		String_t temp(*this);
		temp.ConvertToLower();
		_x = (char)(tolower(_x));
		while(temp[i])
		{
			if(temp[i] == _x)
			{
				return i+1;
			}
			++i;
		}
		return 0;
	}
}

size_t String_t:: GetLast(char _x)const
{
	size_t i = m_length -1;
	
	if(m_caseSens == true)
	{
		while(i >= 0)
		{
			if(string[i] == _x)
			{
				return i+1;
			}
			--i;
		}
		return 0;
	}
	else
	{
		String_t temp(*this);
		temp.ConvertToLower();
		_x = (char)(tolower(_x));
		while(i >= 0)
		{
			if(temp[i] == _x)
			{
				return i+1;
			}
			--i;
		}
		return 0;
	}
}

void String_t::print() const
{
    printf("%s, length: %d\n", string, m_length);
}
/*******************Operators***********************************/
const String_t& String_t:: operator=(const String_t& _origin)
{
	if(this != &_origin)
	{
		CreateFrom(_origin.getString());
	} 
	return *this;
}

const String_t& String_t::operator+=(const String_t& _toAdd)
{ 
	return Prepend(_toAdd);
}

String_t String_t::operator()(unsigned int _start,unsigned int _len) const
{
	if(_start > m_length)
	{
		return *this;
	}
	char* temp = new char[_len+1];
	if(!temp)
	{
		/* TODO*/
	}
	strncpy(temp, &string[_start-1], _len);
	String_t newString(temp);
	delete[] temp;
	return newString;
}

