#ifndef __MEMMANAGER_H__
#define __MEMMANAGER_H__

#include <stddef.h>

class memManager_t
{

public:
    memManager_t();
    virtual ~memManager_t(){};
    
    size_t  GetPos() const;
    size_t  GetSize()const;
    bool   	SetPos(size_t _pos);
    bool    IsEmpty() const;
    
    virtual size_t  ReadData(size_t _pos, size_t _size, char* _buffer) = 0;
    virtual size_t  ReadData(size_t _size, char* _buffer) = 0;
    virtual size_t  WriteData(size_t _pos, size_t _size, char* _obj) = 0;
    virtual size_t  WriteData(size_t _size, char* _obj) = 0;
    
private:
   	memManager_t(const memManager_t& _origin);
    memManager_t& operator= (const memManager_t& _origin);
    
protected:
    size_t  m_size;	
    size_t  m_pos;
    
};

#endif /* __MEMMANAG_H__ */

