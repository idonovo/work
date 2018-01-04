
#ifndef __EXEPTION_H__
#define __EXEPTION_H__

#include <string.h>
#include <iostream>
using namespace std;

template <class T> 
class TExeption_t
{
    public:
        TExeption_t (T& _obj);
        virtual ~TExeption_t ();
        void SetTExeption_t(const char* _fileName, const char* _msg, unsigned int _line);
        friend ostream& operator<<(ostream& _os, TExeption_t<T>& _obj);

    public:
    T m_object;
    char m_msg[32];
    char m_file[32];
    int m_line;
};

template <class T> 
TExeption_t<T>:: TExeption_t(T& _obj)
{
    m_object = _obj;
}
 
template <class T> 
TExeption_t<T>:: ~TExeption_t(){}
   
template <class T>
void TExeption_t<T>:: SetTExeption_t(const char* _fileName, const char* _msg, unsigned int _line)
{

    if(_fileName)
    {
        strcpy(m_file, _fileName);
    }  
	
	if(_msg)
    {
        strcpy(m_msg, _msg);
    }  
    
   	m_line = _line; 
}

template <class T>
ostream& operator<<(ostream& _os, TExeption_t<T>& _obj)
{
    _os<< _obj.m_msg << _obj.m_file << _obj.m_line;
	return _os;

}

#endif
