#ifndef __MYBUFFER_H__
#define __MYBUFFER_H__

#include <string.h>
#include <stdexcept>


namespace advcpp
{

template <class T>
class Buffer_t
{

public:
	
	Buffer_t();
	explicit Buffer_t(std::size_t);
	Buffer_t (const Buffer_t& _buf);
	~Buffer_t ();	
    Buffer_t&operator=(const Buffer_t& _buf); 
         
    void 		SetElement(const T* _t, std::size_t);
    std::size_t GetCapacity()const;
    std::size_t	GetSize()const;
    void		SetSize(std::size_t)const;
	void 		operator+=(const Buffer_t& _buf);
    Buffer_t 	operator+(const Buffer_t& _buf)const;

    T*			GetBuffer()const;
    const T&	operator[](std::size_t _pos)const;
    T&			operator[](std::size_t _pos);
 
private:
	void IncreaseSize(std::size_t);
	   
private:
	T*			m_array;
    std::size_t	m_capacity;
    std::size_t	m_size;
};

template <class T>
Buffer_t<T>::Buffer_t():m_array (new T[1])
,m_capacity(1)
,m_size(1){}

template <class T>
Buffer_t<T>::Buffer_t(std::size_t _size):m_array (new T[_size])
,m_capacity(_size)
,m_size(_size)
{}


template <class T>
Buffer_t<T>::Buffer_t (const Buffer_t& _buf)
{
	m_array =  new T[_buf.m_capacity];// exeption
	m_capacity = _buf.m_capacity;
	m_size = _buf.m_size;
	
	for(unsigned int i =0; i < _buf.m_size; ++i)
	{
		m_array[i] = _buf.m_array[i];
	}	
}

template <class T>
Buffer_t<T>::~Buffer_t ()
{
	delete []m_array;
}

template <class T>
Buffer_t<T>& Buffer_t<T>:: operator=(const Buffer_t& _buf)
{
	if(this != &_buf)
	{
		delete []m_array;
		m_array =  new T[_buf.m_capacity];// exeption
		m_capacity = _buf.m_capacity;
		m_size = _buf.m_size;
	
		for(unsigned int i =0; i < _buf.m_size; ++i)
		{
			m_array[i] = _buf.m_array[i];
		}	
	}
	return *this;
}

template <class T>
void Buffer_t<T>::SetElement(const T* _t, std::size_t _size)
{
	if(m_capacity <= _size)
	{
		IncreaseSize(_size);
	}
	
	for(unsigned int i = 0; i < _size; i++)
	{
		m_array[i] = *(_t + i);
	}
}

template <class T>
void Buffer_t<T>::SetSize(std::size_t _size)const
{
	m_size = _size;
	/*TODO*/
}

template <class T>
std::size_t Buffer_t<T>::GetCapacity()const
{
	return m_capacity;
}

template <class T>
std::size_t Buffer_t<T>::GetSize()const
{
	return m_size;
}

template <class T>
void Buffer_t<T>::IncreaseSize(std::size_t _size)
{
	T* temp_array = new T[_size];// exeption
	for(unsigned int i =0; i < m_size; ++i)
	{
		temp_array[i] = m_array[i];
	}
	m_capacity= _size;
	m_size =  _size;
	delete []m_array;
	m_array = temp_array;
}

template <class T>
Buffer_t<T> Buffer_t<T>::operator+(const Buffer_t& _buf)const
{
	Buffer_t<T> newBuf(*this);
	newBuf+=_buf;
	return newBuf;
}

template <class T>
void  Buffer_t<T>::operator +=(const Buffer_t& _buf)
{
	T* temp =   new T[m_size + _buf.m_size];// exeption
	unsigned int i;
	for(i =0; i < m_size; ++i)
	{
		temp[i] = m_array[i];
	}	

	for(unsigned int x = 0; x < _buf.m_size; ++i, ++x)
	{
		temp[i-1] = _buf.m_array[x];
	}
	
	m_capacity += _buf.m_capacity;
	m_size += _buf.m_size;
	delete []m_array;
	m_array = temp;
}

template <class T>
T* Buffer_t<T>::GetBuffer()const
{
	return m_array;
}

template <class T>
const T& Buffer_t<T>::operator[](std::size_t _pos)const
{
	if(_pos >m_size)
	{
		throw std::out_of_range("out of range");
	}
	return m_array[_pos];
}

template <class T>
T& Buffer_t<T>::operator[](std::size_t _pos)
{
	if(_pos >=m_size)
	{
		throw std::out_of_range("out of range");
	}
	return m_array[_pos];
}

} //namespace
#endif /* __MYBUFFER_H__ */



