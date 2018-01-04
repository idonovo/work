
#include "memPool_t.h"
#include <ctype.h>
#include <string.h>

const size_t default_size = 8;

/*******************Private Funcs******************/
size_t memPool_t::FindPage(size_t _pos, size_t* _offset)
{
	size_t tempPos = 0;
	
	for(unsigned int i = 0; i < m_vec.size(); i += 1)
    { 		
    	if((tempPos += m_vec[i]->GetSize()) >= _pos)
    	{
    		*_offset = tempPos - _pos;
    		return i;
    	}	
    }
}

size_t memPool_t::AddPage()
{
	memPage_t* newPage = new memPage_t(default_size) ;
    m_vec.push_back(newPage);
}
/*******************Public Funcs******************/
memPool_t::memPool_t(): memManager_t()
{
    AddPage();
}

memPool_t::~memPool_t()
{
    for(unsigned int i = 0; i < m_vec.size(); i += 1)
    { 	
    	delete m_vec[i];
    }
}

size_t  memPool_t::ReadData(size_t _pos, size_t _size, char* _buffer) 
{
	
	size_t length, page, offset;
	
	if(_pos >= m_size || !_buffer)
	{
		return 0;
	}
	
	page = FindPage(_pos, &offset);
	
	length = m_vec[page]->ReadData(offset, _size, _buffer);
	
	while(_size > length)
	{
		++page;
		if(page == m_vec.size())
		{
			break;
		}
		_buffer += length;
		length += m_vec[page]->ReadData(0, _size - length, _buffer); 
	}
	
	m_pos = _pos + length;
    
    return length;
	 
}

size_t memPool_t::ReadData(size_t _size, char* _buffer)
{
	return ReadData(m_pos, _size, _buffer);
}

size_t memPool_t::WriteData(size_t _pos, size_t _size, char* _obj)
{
	size_t page, offset;
	
	if(_pos > m_size || !_obj)
	{
		return 0;
	}
	
	page = FindPage(_pos, &offset);
	
	size_t length = m_vec[page]->WriteData(offset, _size, _obj);
	
	while(_size > length)
	{
		++page;
		if(page == m_vec.size())
		{
			AddPage();
		}
		_obj += length;
		length += m_vec[page]->WriteData(0, _size - length, _obj); 
	}
	
	m_pos = _pos + _size;
	m_size += _size;
	
	return _size;
	
}

size_t memPool_t::WriteData(size_t _size, char* _obj)
{
	return WriteData(m_pos, _size, _obj);
}

void memPool_t::SetPageDefaultSize(size_t _size)
{
	memPage_t::SetCapacity(_size);
}



