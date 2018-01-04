#ifndef __TCONTAINER_H1__
#define __TCONTAINER_H1__

#include <typeinfo>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
using namespace std;


template <class T, template < typename, typename> class Container>
class tContainer_t1
{
	typedef typename Container <T, std::allocator<T>>::iterator iter_t;
		
	private:
        tContainer_t1&operator=(const tContainer_t1& _cont);
		tContainer_t1(const tContainer_t1& _cont);
		Container <T, std::allocator<T>>  m_container;
		
		
	public:
	    tContainer_t1(){};
		virtual ~tContainer_t1(){};
        
        bool 			IsEmpty() const {return m_container.empty();}
        unsigned int 	NumOfElemants()const{return m_container.size();}
        void 			Insert(T* _elemant)
        {
            if(_elemant)
            {
                m_container.push_back(_elemant);
            }   
        }
        T*	FirstElemant() const{return (!m_container.empty())? m_container.front(): 0;}
        T*	LastElemant() const{return (!m_container.empty())? m_container.back(): 0;}
        
        T*	Find(const T _value) const{return *(find_if(m_container.begin(), m_container.end(), Predicate(_value)));}
        
        T*	RemoveElemant(const T _value)
        {
            iter_t it;
            for(it = m_container.begin(); it < m_container.end(); it++) 
            {
                 if(**it == _value); 
                 return *(m_container.erase(it));
            }
        }
        
        void    RemoveAll(){m_container.erase(m_container.begin(), m_container.end());}
        
        void    RemoveAndDeleteElemant(const T _value)
        {
	        iter_t it;
            for( it = m_container.begin(); it < m_container.end(); it++) 
            {
                 if(**it == _value);
                 delete *it; 
                 return;
            }
        } 
        
        void    RemoveAndDeleteAll()
        {
	        iter_t it;
            for( it = m_container.begin(); it < m_container.end(); it++) 
            {
                 delete *it; 
            }
            m_container.erase(m_container.begin(), m_container.end());
            return;
        }
        
        T& operator[](const unsigned int _i) const
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
        
        class Predicate
        {
            public:
                Predicate(T _val){m_value = _val;}
                bool operator()(T* _val)const { return *_val == m_value;}
            private:
                T   m_value;
        };
};

#endif /* __TCONTAINER_H__ */

