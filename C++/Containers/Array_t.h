#ifndef __ARRAY_H__
#define __ARRAY_H__

#include "Container_t.h"
#include <stddef.h>
#include <iostream>
using namespace std;

template <class T>

class Array_t: public Container_t<T>
{

public:

    Array_t();
    virtual ~Array_t();
    Array_t(const Array_t& _origin);
   	virtual Array_t& operator=(const Array_t& _origin);
    
    virtual void 			Append(T& _element, unsigned int  _index);
    virtual void  			Prepend(T& _element, unsigned int  _index);
    virtual bool  			Contains(T& _element) const;
    virtual T*	 			Find(T& _element) const;
    virtual int 			Index(T& _element) const;
    virtual void 			Insert(T& _element);
    virtual T* 			    Remove(T& _element);
    virtual void 			RemoveAll();
    virtual void 			RemoveAndDelete(T& _element);
    virtual void 			RemoveAllAndDeleteAll();
    
    void                    Print(ostream& _out) const{for(int i = 0; i< m_size; ++i){_out << *m_array[i] <<endl;}; }

protected:
    void 			Realloc();
    void			ShiftRight(unsigned int _index);
    void			ShiftLeft(int _res);
    
    T** 			m_array;
    unsigned int	m_size;    	
};

template <class T> 
Array_t<T>::Array_t(): Container_t<T>()
{
	m_size = 1024;
	m_array = new T*[m_size];		
}

template <class T> 
Array_t<T>::~Array_t()
{
	delete[] m_array;	
}

template <class T> 
Array_t<T>::Array_t(const Array_t& _origin)
{
	Container_t<T>::m_NumOfElements = _origin.Count();
	m_size = _origin.m_size;
	m_array = new T*[m_size];
	
	for(unsigned int i = 0; i < m_size; ++i)
	{
		m_array[i] = _origin.m_array[i];
	}
}

template <class T> 
Array_t<T>& Array_t<T>::operator=(const Array_t& _origin)
{
	
	if(this != &_origin)
	{
		
		Container_t<T>::m_NumOfElements = _origin.Count();
		delete[] m_array;
		m_size = _origin.m_size;
		m_array = new T*[m_size]; 
		for(unsigned int i = 0; i < m_size; ++i)
		{
			m_array[i] = _origin.m_array[i];
		}
	}
	return *this;
}

template <class T> 
void Array_t<T>::Append(T& _element, unsigned int  _index)
{
	if(_index > Container_t<T>::m_NumOfElements)
	{
		return;
	}
	
	if(Container_t<T>::m_NumOfElements == m_size)
	{
		Array_t<T>::Realloc();
	}
	
	if(_index < Container_t<T>::m_NumOfElements)
	{
		Array_t<T>::ShiftRight(_index+1);
	}
	
	m_array[_index+1] = &_element;
	++Container_t<T>::m_NumOfElements;
	
	return;
}

template <class T> 
void Array_t<T>::Prepend(T& _element, unsigned int  _index)
{
	if(_index > (Container_t<T>::m_NumOfElements + 1) || _index == 0)
	{
		return;
	}
	
	if(Container_t<T>::m_NumOfElements == m_size)
	{
		Array_t<T>::Realloc();
	}
	
	if(_index < Container_t<T>::m_NumOfElements)
	{
		Array_t<T>::ShiftRight(_index);
	}
	
	m_array[_index] = &_element;
	++Container_t<T>::m_NumOfElements;
	
	return;
}

template <class T> 
void Array_t<T>::ShiftRight(unsigned int _index)
{
	for(unsigned int i = Container_t<T>::m_NumOfElements; i <= _index; --i)
	{
		m_array[i] = m_array[i-1];
	}
	return;
}

template <class T> 
void Array_t<T>::Realloc()
{		
	m_size *= 2;
	T** newArray = new T*[m_size];
	for(unsigned int i = 0; i < (m_size/2); ++i)
	{
		m_array[i] = m_array[i];
	}
	delete[] m_array;
	m_array = newArray;
	return;
}

template <class T> 
T* Array_t<T>:: Find(T& _element) const
{
	
	int res = Array_t<T>::Index(_element);
	
	return res == -1? NULL : m_array[res]; 

}

template <class T> 
bool Array_t<T>::Contains(T& _element) const
{
	return (Array_t<T>:: Find(_element));
}

template <class T> 
int Array_t<T>::Index(T& _element) const
{
	for(unsigned int i = 0; i < Container_t<T>::m_NumOfElements; ++i)
	{
		if(*m_array[i] == _element)
		{
			return i;
		}
	}
	return -1;
}

template <class T> 
void Array_t<T>::Insert(T& _element)
{
	if(Container_t<T>::m_NumOfElements == m_size)
	{
		Array_t<T>::Realloc();
	}
	
	m_array[Container_t<T>::m_NumOfElements++] = &_element;
}

template <class T> 
T* Array_t<T>::Remove(T& _element)
{
	int res = Array_t<T>::Index(_element);
	
	if(res == -1)
	{
		return NULL; 
	}
	
	T* toRemove = m_array[res];
	
	Array_t<T>::ShiftLeft(res);
	
	return toRemove;	
}

template <class T> 
void Array_t<T>::ShiftLeft(int _res)
{
	for(unsigned int i = Container_t<T>::m_NumOfElements; i > _res; --i)
	{
		m_array[i-1] = m_array[i];
	}
	return;
}

template <class T> 
void Array_t<T>::RemoveAndDelete(T& _element)
{
	int res = Array_t<T>::Index(_element);
	
	if(res == -1)
	{
		return; 
	}
	
	T* toRemove = m_array[res];
	Array_t<T>::ShiftLeft(res);
	
	delete toRemove;
	
	return;	
}

template <class T> 
void Array_t<T>::RemoveAllAndDeleteAll()
{
	for(unsigned int i =0; i < Container_t<T>::m_NumOfElements ; ++i)
	{
		delete *m_array[i];
	}
	delete[] m_array;
	return;	
}

template <class T> 
void Array_t<T>::RemoveAll()
{
	delete[] m_array;
	return;	
}

#endif /* __ARRAY_H__ */

