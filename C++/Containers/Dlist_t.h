
#ifndef __LIST_H__
#define __LIST_H__

#include "Container_t.h"
#include <stddef.h>

template <class T>
class Dlist_t: public Container_t<T>
{
  public:

    Dlist_t();
    virtual ~Dlist_t(){};
    Dlist_t(const Dlist_t& _origin);
   	virtual Dlist_t& operator= (const Dlist_t& _origin);
    
    virtual void 			Append(T& _element, unsigned int  _index);
    virtual void  			Prepend(T& _element, unsigned int  _index);
    virtual bool  			Contains(T& _element) const;
    virtual T*				Find(T& _element) const;
    virtual int 			Index(T& _element) const;
    virtual void 			Insert(T& _element);
    virtual T*				Remove(T& _element);
    virtual void 			RemoveAll();
    virtual void 			RemoveAndDelete(T& _element);
    virtual void 			RemoveAllAndDeleteAll();

private:
	
	
	class Node_t
	{
		public:
			Node_t(T& _element) {m_data = _element;}
    		virtual ~Node_t(){};
    		Node_t(const Node_t& _origin){m_data = _origin.m_data; m_next = _origin.m_next; m_prev = _origin.m_prev;}
   			virtual Node_t& operator= (const Node_t& _origin){if(this != &_origin) {m_data = _origin.m_data; m_next = _origin.m_next; m_prev = _origin.m_prev;} return *this;}
			
			Node_t *GetPrev() {return m_prev;}
			Node_t *GetNext(){return m_next;}
			Node_t *SetPrev(Node_t * _node){m_prev = _node;}
			Node_t *SetNext(Node_t * _node){m_next = _node;}
			T *GetData(){return m_data;}
			
		private:
			T* m_data;
			Node_t* m_next;
			Node_t* m_prev;
	};
	Node_t* m_first;
	Node_t* m_last;
	
	void    InsertNode(Node_t* prev, Node_t* toInsert, Node_t* next);
	T*      DeleteNode(Node_t* _prev, Node_t* _cur, Node_t* _next);
      
protected:
    unsigned int  m_NumOfElements;	

};

/***********************List Funcs**********************************************/

template <class T> 
Dlist_t<T>::Dlist_t():Container_t<T>()
{
	
	m_first->m_next = m_last;
	m_last-> m_prev = m_first;
}

template <class T> 
Dlist_t<T>::Dlist_t(const Dlist_t& _origin)
{
	
	 m_first = _origin.m_first; 
	 m_last = _origin.m_last;
}

template <class T> 
Dlist_t<T>& Dlist_t<T>:: operator= (const Dlist_t& _origin)
{
    if(this != & _origin)
    {
        m_first = _origin.m_first; 
	    m_last = _origin.m_last;
    }
    return *this;
}


template <class T> 
void Dlist_t<T>:: Append(T& _element, unsigned int _index)
{
    
    if(_index > Container_t<T>::m_NumOfElements)
	{
		return;
	}
	
    Node_t* iterator = m_first;
    
	for(unsigned i = 0; i <_index; ++i)
	{
	    iterator = iterator->m_next;
	}
	
	Node_t* newNode = new Node_t(_element);
	InsertNode(iterator, newNode, iterator->m_next);
    return;
}

template <class T> 
void Dlist_t<T>:: InsertNode(Node_t* prev, Node_t* toInsert, Node_t* next){

	prev->m_next = toInsert;
	next->m_prev = toInsert;
	toInsert->m_next = next;
	toInsert->m_prev = prev;
	
	return;
}

template <class T> 
void Dlist_t<T>:: Prepend(T& _element, unsigned int _index)
{
    
    if(_index > Container_t<T>::m_NumOfElements)
	{
		return;
	}
	
    Node_t* iterator = m_first;
    
	for(unsigned i = 0; i <_index; ++i)
	{
	    iterator = iterator->m_next;
	}
	
	Node_t* newNode = new Node_t(_element);
	InsertNode(iterator->m_prev, newNode, iterator);
    return;
}

template <class T> 
void Dlist_t<T>:: Insert(T& _element)
{
	Node_t* newNode = new Node_t(_element);
	InsertNode(m_last->m_prev, newNode, m_last);
    return;
}

template <class T> 
int Dlist_t<T>:: Index(T& _element) const
{
    Node_t* iterator = m_first;
    
    for(unsigned int i = 0; i<Container_t<T>::m_NumOfElements;++i)
    {
        iterator = iterator->m_next;
        
        if(*(iterator->GetData()) == _element)
        {
            return i;
        }
    }
    return -1; 
}

template <class T> 
T* Dlist_t<T>:: Find(T& _element) const
{
    Node_t* iterator = m_first;
    
    for(unsigned int i = 0; i<Container_t<T>::m_NumOfElements;++i)
    {
        iterator = iterator->m_next;
        
        if(*(iterator->GetData()) == _element)
        {
            return *(iterator->GetData());
        }
    }
    return NULL; 
}

template <class T> 
bool Dlist_t<T>:: Contains(T& _element) const
{
    return (Dlist_t<T>:: Find(_element)); 
}

template <class T> 
T* Dlist_t<T>:: Remove(T& _element)
{
    Node_t* iterator = m_first;
    
    while(iterator != m_last)
    {
        iterator = iterator->m_next;
        
        if(*(iterator->GetData()) == _element)
        {
            return DeleteNode(iterator->m_prev, iterator, iterator->m_prev);
        }
    }
    return NULL; 
}

template <class T> 
T* Dlist_t<T>::DeleteNode(Node_t* _prev, Node_t* _cur, Node_t* _next)
{
    T* data;
    _prev->m_next = _next;
    _next->m_prev = _prev;
    data = _cur.GetData();
    delete _cur;
    return data;
}

template <class T> 
void Dlist_t<T>:: RemoveAndDelete(T& _element)
{
    T* data = Dlist_t<T>::Remove(_element);
    if(data)
    {
        delete data;
    }
    return; 
}

template <class T> 
void Dlist_t<T>:: RemoveAll()
{
    Node_t* iterator = m_first;
    
    while(m_first != m_last)
    {
        m_first = m_first->m_next;
        DeleteNode(m_first->_prev, m_first, m_first->m_next);    
    }
    return; 
}

template <class T> 
void Dlist_t<T>:: RemoveAllAndDeleteAll()
{
    Node_t* iterator = m_first;
    
    while(m_first != m_last)
    {
        m_first = m_first->m_next;
        delete DeleteNode(m_first->_prev, m_first, m_first->m_next);    
    }
    return NULL; 
}

#endif /* __LIST_H__ */
