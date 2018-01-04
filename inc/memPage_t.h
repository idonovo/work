#ifndef __MEMPAGE_H__
#define __MEMPAGE_H__

#include <stddef.h>
#include <vector>
#include "memManager_t.h"

class memPage_t: public memManager_t
{

public:
    memPage_t(size_t _size);
    ~memPage_t ();
    
    virtual size_t  ReadData(size_t _pos, size_t _size, char* _buffer);
    virtual size_t  ReadData(size_t _size, char* _buffer);
    virtual size_t  WriteData(size_t _pos, size_t _size, char* _obj);
    virtual size_t  WriteData(size_t _size, char* _obj);
    
    bool	                IsFull()const;  
    inline  static void		SetCapacity(size_t _size){m_capacity = _size;}
    inline  static size_t	GetNumOgPages(){return m_nop;}
    
private:
   	memPage_t(const memPage_t& _origin);
    memPage_t& operator=(const memPage_t& _origin);
    
    void 	SetSize(size_t _length);
    size_t  SetLength(size_t _size, size_t _pos);
    void	SetMyCapacity(size_t _size){my_capacity = _size;}
    size_t  ReadFromPage(size_t _pos, size_t _size, char* _buffer);
    
protected:
    static	size_t 	m_capacity;
    size_t 			my_capacity;
    static	size_t 	m_nop;
    char*   		m_data;

};

#endif /* __MEMPAGE__ */

