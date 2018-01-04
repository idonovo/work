#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include <stddef.h>

template <class T>
class Container_t
{

public:

    Container_t();
    virtual ~Container_t(){};
    Container_t(const Container_t& _origin);
   	virtual Container_t& operator= (const Container_t& _origin);
    
   	unsigned int   Count() const;
    bool		   IsEmpty() const;
    
    virtual void 			Append(T& _element, unsigned int  _index) = 0;
    virtual void  			Prepend(T& _element, unsigned int  _index) = 0;
    virtual bool  			Contains(T& _element) const = 0;
    virtual T*				Find(T& _element) const = 0;
    virtual int 			Index(T& _element) const = 0;
    virtual void 			Insert(T& _element) = 0;
    virtual T*				Remove(T& _element) = 0;
    virtual void 			RemoveAll() = 0;
    virtual void 			RemoveAndDelete(T& _element) = 0;
    virtual void 			RemoveAllAndDeleteAll() = 0;
      
protected:
    unsigned int  m_NumOfElements;	
};

template <class T> 
Container_t<T>::Container_t()
{
	m_NumOfElements = 0;
}

template <class T> 
Container_t<T>::Container_t(const Container_t& _origin)
{
	m_NumOfElements = _origin.Count();	
}


template <class T> 
Container_t<T>& Container_t<T>::operator= (const Container_t& _origin)
{
	if(this != &_origin)
	{
		m_NumOfElements = _origin.Count();	
	}
	return *this;
}


template <class T> 
unsigned int Container_t<T>::Count() const
{
	return m_NumOfElements;
}

template <class T> 
bool Container_t<T>:: IsEmpty() const
{
	return (m_NumOfElements == 0);
}





#endif /* __CONTAINER_H__ */

