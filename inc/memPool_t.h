#ifndef __MEMPOOL_H__
#define __MEMPOOL_H__

#include <stddef.h>
#include <vector>
#include <iostream>

#include "memManager_t.h"
#include "memPage_t.h"

class memPool_t: public memManager_t
{

public:
    memPool_t ();
    ~memPool_t();
    
    virtual size_t  ReadData(size_t _pos, size_t _size, char* _buffer);
    virtual size_t  ReadData(size_t _size, char* _buffer);
   	virtual size_t  WriteData(size_t _pos, size_t _size, char* _obj);
    virtual size_t  WriteData(size_t _size, char* _obj); 
    
  	void	SetPageDefaultSize(size_t _size);
    
private:
   	memPool_t(const memPool_t& _origin);
    memPool_t& operator=(const memPool_t& _origin);
    size_t FindPage(size_t _pos, size_t* _offset);
    size_t AddPage();
    
protected:
    std::vector<memPage_t*> m_vec;

};



#endif /* __MEMPOOL_H__*/

