#ifndef __MYSHARED_PTR_H__
#define __MYSHARED_PTR_H__

#include <pthread.h>
#include "Guard.h"
#include <cstddef>


namespace advcpp
{

//class ReferanceCounter
//{
//public:	
//	ReferanceCounte-r():counter(0){}
//	
//	std::size_t Add()
//	{
//		return ++counter;
//	}
//	
//	std::size_t Release()
//	{
//		return --counter;
//	}
//	
//	std::size_t counter; 
//};


template <class T>
class Shared_Ptr
{

template<class X>
friend class Shared_Ptr;

public:
	static std::size_t* CreateRef();
	static std::size_t* CreateDummy();
	static std::size_t* (*Create[2])(void);
	
	Shared_Ptr ();
	explicit Shared_Ptr (T*);
	 ~Shared_Ptr ();
	
	template <class X>
	Shared_Ptr (const Shared_Ptr<X>&);
	Shared_Ptr (const Shared_Ptr&);
	
	template<class X>
	Shared_Ptr& operator= (const Shared_Ptr<X>&);	
	Shared_Ptr& operator= (const Shared_Ptr&);
	Shared_Ptr& operator= (T*);
	
	T& 			operator*();
	T* 			operator->();
	operator T*(); // To discuss in class. Mayers may not be pleased...	
	bool 		operator== (const Shared_Ptr&) const;
	bool 		operator== (const T*)const;
	const T*	GetPtr() const;
	std::size_t GetCounter() const;

private:	
	void        Destract();
	void        Init(const Shared_Ptr&);
	typedef void (Shared_Ptr::*bool_type)() const;
	void this_type_does_not_support_comparisons() const {} // to support safe bool idiom;

public:	
	operator bool_type()const;  
	
private:
	T* m_data;
	std::size_t* 	m_ref;
	static std::size_t NullRefCounter;
};

template <class T>
std::size_t* (*Shared_Ptr<T>::Create[2])(void) = {Shared_Ptr<T>::CreateDummy, Shared_Ptr<T>::CreateRef};
 
template <class T>
std::size_t  Shared_Ptr<T>::NullRefCounter = 1;

template <class T>
inline Shared_Ptr<T>::Shared_Ptr(): m_data(0)
{
	m_ref = Create[0]();
}

template <class T>
std::size_t* Shared_Ptr<T>::CreateRef()
{
	return new std::size_t(1);
}

template <class T>
std::size_t* Shared_Ptr<T>::CreateDummy()
{
	return &(++NullRefCounter);
}

template <class T>
inline Shared_Ptr<T>::Shared_Ptr(T* _ptr): m_data(_ptr)
{
	try
	{
		m_ref = (Create[bool(_ptr)])();
	}
	catch(...)
	{
		delete _ptr;
		throw;
	}
}

template <class T>
inline void  Shared_Ptr<T>::Destract()
{
    if(!__sync_bool_compare_and_swap(m_ref, 0, 0))
	{	
		__sync_fetch_and_sub(m_ref, 1);
		if(__sync_bool_compare_and_swap(m_ref, 0, 0))
		{
			delete m_data;
			delete m_ref;
		}
	}
}

template <class T>
inline void  Shared_Ptr<T>::Init(const Shared_Ptr& _obj)
{
    m_data = _obj.m_data;
	m_ref = _obj.m_ref;
	__sync_fetch_and_add(m_ref, 1);
}

template <class T>
inline Shared_Ptr<T>::~Shared_Ptr()
{
    Destract();
}

template <class T>
inline Shared_Ptr<T>::Shared_Ptr(const Shared_Ptr& _obj)
{
	Init(_obj);
}

template <class T>
template <class X>
inline Shared_Ptr<T>::Shared_Ptr (const Shared_Ptr<X>& _obj)
{
	m_data = _obj.m_data;
	m_ref = _obj.m_ref;
	__sync_fetch_and_add(m_ref, 1);

}

template <class T>
inline Shared_Ptr<T>& Shared_Ptr<T>::operator= (const Shared_Ptr& _obj)
{
	if(this != &_obj)
	{	
		Destract();
		
		Init(_obj);
	}
	return *this;
}

template <class T>
template<class X>
Shared_Ptr<T>&  Shared_Ptr<T>::operator= (const Shared_Ptr<X>& _obj)
{
	if(this != &_obj)
	{	
		Destract();

        m_data = _obj.m_data;
        m_ref = _obj.m_ref;
        __sync_fetch_and_add(m_ref, 1);
	}
	return *this;
}

template <class T>
inline Shared_Ptr<T>& Shared_Ptr<T>::operator= (T* _ptr)  //???
{
	
	Destract();
	m_data = _ptr;
	m_ref = (Create[bool(_ptr)])();

	return *this;
}

template <class T>
inline T& 	 Shared_Ptr<T>::operator*()
{
	return *m_data;
}

template <class T>
inline T*  Shared_Ptr<T>::	operator->()
{
	return m_data;
}

template <class T>
inline bool Shared_Ptr<T>::operator== (const Shared_Ptr& _obj) const
{
	return (m_data == _obj.m_data);
}

template <class T>
inline bool Shared_Ptr<T>::operator== (const T* _ptr) const
{
	return (m_data == _ptr);
}

template <class T>
inline const T* Shared_Ptr<T>::GetPtr() const
{
	return m_data; 
}

template <class T>
inline std::size_t Shared_Ptr<T>::GetCounter() const
{
	return *m_ref;
}

template <class T>
inline Shared_Ptr<T>::operator bool_type()const
{
	return m_data? &Shared_Ptr<T>::this_type_does_not_support_comparisons: 0;
} 

template <class T>
inline Shared_Ptr<T>::operator T*()
{
    return m_data;
}

}// namespace


#endif /* __MYSHARED_PTR_H__ */

