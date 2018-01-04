#ifndef __MYBITCET_H__
#define __MYBITCET_H__

#include <cstring>
#include <limits.h>
#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <iostream>
	
namespace advcpp
{

template<std::size_t SIZE,class T = unsigned int>
class BitSet
{
public:
	
	static const std::size_t bitesForT = sizeof(T) * CHAR_BIT;
	static const std::size_t numOfT = SIZE/bitesForT+ (SIZE%bitesForT > 0);
	
	class BitReference
	{
		public:
  		explicit BitReference(T* const _t, std::size_t _offset);                                 
  		//~BitReference();
  		operator bool()const;                           
  		BitReference&   operator= (bool x); 
  		BitReference&  	operator= (const BitReference& x); 
  		bool   			operator== (bool x) const;               
  		bool 			operator== (const BitReference& x) const;         
 		void    		flip();                               
		bool			IsBitSet() const;
		void			BitOn();
		void			BitOff();
  		
  		private: 
  		T*		m_t;
  		std::size_t m_offset;	                    
	};
	
	explicit BitSet (unsigned int*);
	~BitSet ();
	BitSet(const BitSet&);
	BitSet& operator=(const BitSet&);
	
	bool           		operator[](std::size_t) const;
	BitReference 		operator[](std::size_t);
	bool   				operator ==(const BitSet&)const;
	bool 	        	GetBit(std::size_t);
	void		    	BitOn(std::size_t);
	void		    	BitOff(std::size_t);
	
	
	template<T(*Operator)(T& _a, const T& _b)>
	void BitWiseLoop(BitSet<SIZE,T>& _set);
	const BitSet&   	operator &=(BitSet&);
	const BitSet&   	operator |=(BitSet&);
	const BitSet&   	operator ^=(BitSet&);
	const BitSet&   	operator ~(void);	
	const BitSet&   	operator <<=(std::size_t _shifts);
	const BitSet& 		operator >>=(std::size_t _shifts);
	
	std::size_t 		Count();
	
	template<bool(*Operator)(const T&)>
	bool					QueryLoop();	
	bool 					Any();
	bool 					All();
	bool  					None();
	
private:
	void                SetBitSet(unsigned int* _bits);
	T*                  LocateT(std::size_t index) const;
	std::size_t	        CalcOffset(std::size_t index) const;
	void				ZerofyTail();
	
	T* 			m_set;
};

/**********************************************************************************/
//							BitReference
/**********************************************************************************/
template<std::size_t SIZE,class T>
BitSet<SIZE,T>::BitReference::BitReference(T* const _t, std::size_t _offset): 
m_t(_t)
, m_offset(_offset){} 

template<std::size_t SIZE,class T>
inline BitSet<SIZE,T>::BitReference::operator bool() const
{
	return IsBitSet();
}

template<std::size_t SIZE,class T>
inline void BitSet<SIZE,T>::BitReference::BitOn()
{
	*m_t |= 1 << m_offset;
}

template<std::size_t SIZE,class T>
inline void BitSet<SIZE,T>::BitReference::BitOff()
{
	*m_t &= ~(1 << m_offset);
}

template<std::size_t SIZE,class T>
inline bool BitSet<SIZE,T>::BitReference::IsBitSet() const
{
	T mask = 1 <<m_offset;
	return (*m_t & mask) != 0;
}

template<std::size_t SIZE,class T>
inline typename BitSet<SIZE,T>::BitReference& BitSet<SIZE,T>::BitReference::operator= (bool x)
{
	x?BitOn(): BitOff();
	return *this;
}   

template<std::size_t SIZE,class T>
inline typename BitSet<SIZE,T>::BitReference& BitSet<SIZE,T>::BitReference::operator= (const BitReference& x)
{
  	*this = bool(x);
    return *this;
}

template<std::size_t SIZE,class T>
inline void BitSet<SIZE,T>::BitReference::flip()
{
    IsBitSet()? BitOff(): BitOn();
}

template<std::size_t SIZE,class T>
inline bool BitSet<SIZE,T>::BitReference::operator== (bool x) const
{
    return IsBitSet() == x;
}

template<std::size_t SIZE,class T>
inline bool BitSet<SIZE,T>::BitReference::operator== (const BitReference& x) const
{
    return IsBitSet() == x.IsBitSet();
}

/**********************************************************************************/
//							Query Helpers
/**********************************************************************************/

template<class T>
struct Sum
{
   	public:
   	Sum():sum(0){}
   	void operator()(const T& _t)
   	{
   		for(unsigned int i = 0; i <sizeof(T) * CHAR_BIT; ++i)
   		{
   			if(_t & (1 << i))
   			{
   				++sum;
   			}
   		}
   	}
	std::size_t sum;
};

template<class T>
inline bool CheckAny(const T& _t)
{
	T mask = 0;
	return (_t & ~mask) != 0;
}

template<class T>
inline bool CheckAll(const T& _t)
{
	T mask = 0;
	return _t == ~mask;
}

/**********************************************************************************/
//							Queries
/**********************************************************************************/
template<std::size_t SIZE,class T>
inline std::size_t BitSet<SIZE,T>::Count()
{
	Sum<T> s = std::for_each(m_set, m_set + numOfT, Sum<T>());
	return s.sum;
}

template<std::size_t SIZE,class T>
template<bool(*Query)(const T&)>
inline bool BitSet<SIZE,T>::QueryLoop()
{
	 return m_set+numOfT != std::find_if(m_set, m_set + numOfT, Query);
}

template<std::size_t SIZE,class T>
inline bool BitSet<SIZE,T>::Any()
{
	return QueryLoop<CheckAny>();
}

template<std::size_t SIZE,class T>
inline bool BitSet<SIZE,T>::All()
{
   return  QueryLoop<CheckAll>();
}

template<std::size_t SIZE,class T>
inline bool  BitSet<SIZE,T>::None()
{
    return !QueryLoop<CheckAny>();
}

template<std::size_t SIZE,class T>
inline bool  BitSet<SIZE,T>::operator ==(const BitSet& _set) const
{
	return std::equal(m_set, m_set + numOfT, _set.m_set);
}
/**********************************************************************************/
//							external operators
/**********************************************************************************/
template<std::size_t SIZE,class T>
inline std::ostream& operator<<(std::ostream& _os, const BitSet<SIZE,T>&  _set)
{
	_os<< "BitSet:"; 
	for(unsigned int i = 0; i < SIZE; ++i) 
	{
	   _os << int(_set[i]) << "  ";
	}
	_os<< std::endl;
	return _os;
}

template<std::size_t SIZE,class T>
inline BitSet<SIZE,T>  operator &(const BitSet<SIZE,T>& _a, const BitSet<SIZE,T>& _b)
{
    return BitSet<SIZE,T> (_a) &= _b;
}

template<std::size_t SIZE,class T>
inline BitSet<SIZE,T>  operator |(const BitSet<SIZE,T>& _a, const BitSet<SIZE,T>& _b)
{
    return BitSet<SIZE,T> (_a) |= _b;
}

template<std::size_t SIZE,class T>
inline BitSet<SIZE,T>  operator ^(const BitSet<SIZE,T>& _a, const BitSet<SIZE,T>& _b)
{
    return BitSet<SIZE,T> (_a) ^= _b;
}

template<std::size_t SIZE,class T>
inline BitSet<SIZE,T> 	operator <<(const BitSet<SIZE,T>& _a, std::size_t _shifts)
{
	return BitSet<SIZE,T> (_a) <<= _shifts;
}

template<std::size_t SIZE,class T>
inline BitSet<SIZE,T> 	operator >>(const BitSet<SIZE,T>& _a, std::size_t _shifts)
{
	return BitSet<SIZE,T> (_a) >>= _shifts;
}

/**********************************************************************************/
//							Init Functor
/**********************************************************************************/
template<class T>
struct BitSetInitilizer
{
   	public:
   	BitSetInitilizer(unsigned int* _array,unsigned int _bitesForT):m_array(_array), m_bitesForT(_bitesForT){}
   	void operator()(T& _t)
   	{
		for(unsigned int x = 0; x < m_bitesForT; ++x, ++m_array)
		{			
			if(*m_array)
			{
				_t |= 1 << x;
			}
		}  
   	} 	
	unsigned int* 	m_array;
	unsigned int	m_bitesForT;
};

/**********************************************************************************/
//							Ctor's - Assignment - Dtor
/**********************************************************************************/
template<std::size_t SIZE,class T>
BitSet<SIZE,T>::BitSet (unsigned int* _bits)
{
	if(!_bits)
	{
		throw std::invalid_argument("null_ptr");
	}
	m_set = new T[numOfT];
	SetBitSet(_bits);
}

template<std::size_t SIZE,class T>
BitSet<SIZE,T>::BitSet(const BitSet& _bitSet)
{
	m_set = new T[numOfT];
	std::copy(_bitSet.m_set, _bitSet.m_set + numOfT, m_set);

}

template<std::size_t SIZE,class T>
inline BitSet<SIZE,T>& BitSet<SIZE,T>::operator=(const BitSet& _bitSet)
{
	if(this != & _bitSet)
	{
		delete []m_set;
		m_set = new T[numOfT];
		std::copy(_bitSet.m_set, _bitSet.m_set + numOfT, m_set);	
	}
	return *this;
}

template<std::size_t SIZE,class T>
inline void BitSet<SIZE,T>::SetBitSet(unsigned int* _bits)
{	
	std::fill(m_set, m_set + numOfT, 0);
	std::for_each(m_set, m_set + numOfT, BitSetInitilizer<T>(_bits, bitesForT));
}

template<std::size_t SIZE,class T>
BitSet<SIZE,T>::~BitSet ()
{
	delete[]m_set;
}

/**********************************************************************************/
//							Modify 
/**********************************************************************************/
template<std::size_t SIZE,class T>
inline typename BitSet<SIZE,T>::BitReference BitSet<SIZE,T>::operator[](std::size_t _index)
{
    if(_index > SIZE)
	{
		throw std::out_of_range("out_of_range");
	} 
    BitReference x(LocateT(_index),CalcOffset(_index));
    return x;
}

template<std::size_t SIZE,class T>
inline bool BitSet<SIZE,T>:: operator[](std::size_t _index) const
{
	
	if(_index > SIZE)
	{
		throw std::out_of_range("out_of_range");
	} 
	BitReference x(LocateT(_index),CalcOffset(_index));
    return x;
}

template<std::size_t SIZE,class T>
inline bool  BitSet<SIZE,T>::GetBit(std::size_t _index)
{
    BitReference x(LocateT(_index),CalcOffset(_index));
    return x; 
}

template<std::size_t SIZE,class T>
inline void BitSet<SIZE,T>::BitOn(std::size_t _index)
{
    BitReference x(LocateT(_index),CalcOffset(_index));
    x.BitOn();
}

template<std::size_t SIZE,class T>
inline void BitSet<SIZE,T>::BitOff(std::size_t _index)
{
    BitReference x(LocateT(_index),CalcOffset(_index));
    x.BitOff();
}

/**********************************************************************************/
//							Privates Func's for modifiers 
/**********************************************************************************/
template<std::size_t SIZE,class T>
inline T*  BitSet<SIZE,T>::LocateT(std::size_t index) const
{
    return &m_set[index/bitesForT];
}

template<std::size_t SIZE,class T>
inline std::size_t  BitSet<SIZE,T>::CalcOffset(std::size_t index) const
{
    return index%bitesForT;
}

template<std::size_t SIZE,class T>
inline void  BitSet<SIZE,T>::ZerofyTail()
{
	if(SIZE%bitesForT)
	{
		m_set[numOfT] <<= SIZE%bitesForT;
		m_set[numOfT] >>= SIZE%bitesForT;
	}
}

/**********************************************************************************/
//							Template Bitwise Operators
/**********************************************************************************/
template<class T>
inline T AndOp(T& _a, const T& _b)
{
	return _a &= _b;
}

template<class T>
inline T OrOp(T& _a, const T& _b)
{
	return _a |= _b;
}

template<class T>
inline T XorOp(T& _a, const T& _b)
{
	return _a ^= _b;
}

template<class T>
inline T FlipOp(T& _a)
{
	return _a = ~_a;
}

/**********************************************************************************/
//							Class Bitwise Equal Operators
/**********************************************************************************/
template<std::size_t SIZE,class T>
template<T(*Operator)(T& _a, const T& _b)>
inline void BitSet<SIZE,T>::BitWiseLoop(BitSet<SIZE,T>& _set)
{
	 std::transform(m_set, m_set + numOfT, _set.m_set, m_set, Operator);
}

template<std::size_t SIZE,class T>
inline const BitSet<SIZE,T>& BitSet<SIZE,T>::operator &=(BitSet& _set)
{
   	BitWiseLoop<AndOp<T> >(_set);     
	return *this;
}

template<std::size_t SIZE,class T>
inline const BitSet<SIZE,T>& BitSet<SIZE,T>::operator |=(BitSet& _set)
{
    BitWiseLoop<OrOp<T> >(_set); 
	return *this;
}

template<std::size_t SIZE,class T>
inline const BitSet<SIZE,T>& BitSet<SIZE,T>::operator ^=(BitSet& _set)
{
    BitWiseLoop<XorOp<T> >(_set);
	return *this;
}

template<std::size_t SIZE,class T>
inline const BitSet<SIZE,T>& BitSet<SIZE,T>::operator ~()
{	
     std::transform(m_set, m_set + numOfT,  m_set, FlipOp<T>);
     ZerofyTail();
     return *this;
}

/**********************************************************************************/
//							Shift Functors
/**********************************************************************************/
template<class T>
struct ShiftLeft
{
	ShiftLeft(std::size_t _sizeOfT): m_sizeOfT(_sizeOfT), m_lastBit(false){}
	void operator()(T& _t)
   	{
		bool temp = m_lastBit;
		m_lastBit =  (m_lastBit & 1 << m_sizeOfT) != 0;
		_t <<= 1;
		_t |= temp;
   	} 
	bool m_lastBit;
	std::size_t m_sizeOfT;
};

template<class T>
struct ShiftRight
{
	ShiftRight(std::size_t _sizeOfT): m_sizeOfT(_sizeOfT),  m_firstBit(false){}
	void operator()(T& _t)
   	{ 
		bool temp = _t & 1;
		_t >>= 1;
		_t |= (m_firstBit << m_sizeOfT);
		m_firstBit = temp;
   	} 
	bool m_firstBit;
	std::size_t m_sizeOfT;
};

/**********************************************************************************/
//							Class Shift Operators
/**********************************************************************************/
template<std::size_t SIZE,class T>
inline const BitSet<SIZE,T>& BitSet<SIZE,T>::operator <<=(std::size_t _shifts)
{
	for(unsigned int i = 0; i < SIZE-_shifts ; ++i)
	{
		(*this)[i+_shifts] = (*this)[i];
		//std::for_each(m_set, m_set + numOfT, ShiftLeft<T>(bitesForT));
	}
	
	for(unsigned int i = 0; i < _shifts ; ++i)
	{
		(*this)[i] = 0;
	}
	ZerofyTail();
    return *this;
}

template<std::size_t SIZE,class T>
inline const BitSet<SIZE,T>& BitSet<SIZE,T>::operator >>=(std::size_t _shifts)
{

	for(unsigned int i = 0; i < SIZE-_shifts; ++i)
	{
		(*this)[i] = (*this)[i+_shifts];
	}
	
	for(unsigned int i = SIZE; i >= (SIZE - _shifts) ; --i)
	{
		(*this)[i] = 0;
	}
	
//	for(unsigned int x = 0; x < _shifts; ++x)
//	{
//		//std::for_each(m_set, m_set + numOfT, ShiftRight<T>(bitesForT));
//	}
    return *this;
}


} //namespace
#endif /* __MYBITCET_H__ */

