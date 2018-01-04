#ifndef __TCONTAINER_H__
#define __TCONTAINER_H__

#include <typeinfo>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
using namespace std;


template <class T, class Container>
class tContainer_t
{
	typedef typename Container::iterator iter_t;
	
	public:
	    tContainer_t();
		virtual ~tContainer_t ();
        
        bool 			IsEmpty() const;
        unsigned int 	NumOfElemants()const;
        void 			Insert(T* _elemant);
        T*				FirstElemant() const;
        T*				LastElemant() const;
        T*				Find(const T _value) const;
        T*				RemoveElemant(const T _value);
        void			RemoveAll();
        void			RemoveAndDeleteElemant(const T _value);
        void			RemoveAndDeleteAll();
        T& operator[](const unsigned int _i) const;
        
        class Predicate
        {
            public:
                Predicate(T _val){m_value = _val;}
                bool operator()(T* _val)const { return *_val == m_value;}
            private:
                T   m_value;
        };   
		
	private:
        tContainer_t&operator=(const tContainer_t& _cont);
		tContainer_t(const tContainer_t& _cont);
		Container m_container;
};

template <class T, class Container>
tContainer_t<T, Container>:: tContainer_t(){}

template <class T, class Container>
tContainer_t<T, Container>:: ~tContainer_t(){}

template <class T, class Container>
bool tContainer_t<T, Container>:: IsEmpty() const
{
	return m_container.empty();
}

template <class T, class Container>
unsigned int tContainer_t<T, Container>:: NumOfElemants()const
{
	return m_container.size();
}

template <class T, class Container>
void tContainer_t<T, Container>:: Insert(T* _elemant)
{
	if(_elemant)
	{
	    m_container.push_back(_elemant);
	}
}

template <class T, class Container>
T* tContainer_t<T, Container>:: FirstElemant() const
{
	
	return (!m_container.empty())? m_container.front(): 0;
}

template <class T, class Container>
T* tContainer_t<T, Container>:: LastElemant() const
{
	return (!m_container.empty())? m_container.back(): 0;
}

template <class T, class Container>
T* tContainer_t<T, Container>::RemoveElemant(const T _value)
{
	iter_t it;
    for(it = m_container.begin(); it < m_container.end(); it++) 
    {
         if(**it == _value); 
         return *(m_container.erase(it));
    }
}

template <class T, class Container>
void tContainer_t<T, Container>::RemoveAll()
{
	m_container.erase(m_container.begin(), m_container.end());
}

template <class T, class Container>
void tContainer_t<T, Container>::RemoveAndDeleteElemant(const T _value)
{
	iter_t it;
    for( it = m_container.begin(); it < m_container.end(); it++) 
    {
         if(**it == _value);
         delete *it; 
         return;
    }
}

template <class T, class Container>
void tContainer_t<T, Container>::RemoveAndDeleteAll()
{
	iter_t it;
    for( it = m_container.begin(); it < m_container.end(); it++) 
    {
         delete *it; 
    }
    m_container.erase(m_container.begin(), m_container.end());
    return;
}

template <class T, class Container>
T* tContainer_t<T, Container>:: Find(const T _value) const
{
    return *(find_if(m_container.begin(), m_container.end(), Predicate(_value)));
}

template <class T, class Container>
T& tContainer_t<T, Container>::operator[](const unsigned int _i) const
{
    iter_t it;
            it = m_container.begin();
    if(typeid(m_container) == typeid(vector<T*>))
    {
        if(_i <= m_container.size())
        {
            return *(m_container[_i]);
        }
    }
    if(typeid(m_container) == typeid(list<T*>))
    {
        if(_i <= m_container.size())
        {  
            return **(it);
        }
    }
} 
#endif /* __TCONTAINER_H__ */

