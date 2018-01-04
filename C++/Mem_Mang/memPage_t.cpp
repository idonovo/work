
#include "memPage_t.h"
#include <ctype.h>
#include <string.h>

const size_t default_size = 8;

size_t  memPage_t::	m_capacity = default_size;
size_t 	memPage_t::m_nop = 0;

/*******************Private Funcs******************/
void memPage_t::SetSize(size_t _length)
{
    m_size += _length;
}

size_t memPage_t::SetLength(size_t _size, size_t _pos)
{
    if(_pos + _size > m_capacity)
    {
    	return m_capacity - _pos;
    }
    else
    {
    	return _size;
    }
}

size_t memPage_t::ReadFromPage(size_t _pos, size_t _size, char* _buffer)
{
    size_t length;
    
    if(!_buffer || _pos > m_size)
    {
    	return 0;
    }
    
    if(_pos + _size > m_size)
    {
    	length = m_size - _pos;
    }
    else
    {
    	length = _size;
    }
    memcpy(_buffer, m_data +_pos, length);
    
    return length;
}

/*******************Public Funcs******************/
memPage_t::memPage_t(size_t _size): memManager_t()
{
    if(!_size)
    {
        m_capacity = default_size;
    }
    else
    {
        m_capacity = _size;
    }
    
    m_data = new char[m_capacity];
    if(!m_data){/*TODO*/}
    ++m_nop;
}

memPage_t::~memPage_t()
{
    --m_nop;
    delete[] m_data;
}
    
size_t  memPage_t::ReadData(size_t _pos, size_t _size, char* _buffer)
{
    size_t length = ReadFromPage(_pos, _size, _buffer);
    
    m_pos = _pos + length;
    
    return length;
}

size_t  memPage_t::ReadData(size_t _size, char* _buffer)
{
    size_t length = ReadFromPage(m_pos, _size, _buffer);

    m_pos =+ length;
    
    return length;   
}

size_t memPage_t::WriteData(size_t _pos, size_t _size, char* _obj)
{
    if(!_obj || _pos > m_size)
    {
        return 0;
    }
     
    size_t length = SetLength(_size, _pos);
    
    memcpy(m_data + _pos, _obj, length);
    SetSize((int)_pos - (int)m_size + (int)length);
    
    return length;
}

size_t  memPage_t::WriteData(size_t _size, char* _obj)
{
    
    if(!_obj)
    {
    	return 0;
    } 
    
    size_t length = SetLength(_size, m_pos);
      
    memcpy( m_data + m_size, _obj, length);
    
    SetSize(length);
    
    return length;
}

bool memPage_t::IsFull()const
{
	return (m_capacity == m_size);
}


