#include "memManager_t.h"
#include <ctype.h>
#include <string.h>

/*****************************************************/
memManager_t::memManager_t()
{
	m_size = 0;	
    m_pos = 0;
}

size_t memManager_t::GetPos() const
{
	return m_pos;
} 

bool memManager_t::SetPos(size_t _pos)
{
	
	if(_pos <= m_pos)
	{
		m_pos = _pos;
		return true;
	} 
    char* r = "shai ma hamatzav?";
    throw r;
	return false;
}

size_t memManager_t::GetSize(void) const
{
	return m_size;
} 

bool memManager_t::IsEmpty(void) const
{
	return m_size == 0 ? true : false;
}





 
