#ifndef __STREET_H__
#define __STREET_H__

#include <vector>
#include <iostream>

#include "Building_t.h"

template <class T1, class T2> 
class Street_t
{

public:
	Street_t(T1& _streetId);
	virtual ~Street_t();
	
	Street_t(const Street_t& _b);  
	const Street_t& operator=(Street_t& _b);
	
	void 			SetStreetID(const T1 _id);	
	T1&				GetStreetID()const;
	void 			AddBuilding(Building_t<T2>& newBuilding);	
	Building_t<T2>&	GetBuilding(T2& _id)const;
	
	unsigned int	GetStreetSize()const;
	
private:
	T1 m_id;
	std::vector<Building_t<T2>*> m_vec;
}; 


template <class T1, class T2> 
Street_t< T1, T2> :: Street_t(T1& _streetId)
{
	m_id = _streetId;	
}

template <class T1, class T2> 
Street_t<T1, T2> :: ~Street_t()
{
	for(unsigned int i = 0; i < m_vec.size(); i += 1)
    { 	
    	delete m_vec[i];
    }
}

template <class T1, class T2> 
Street_t<T1, T2> :: Street_t(const Street_t& _b)
{
	m_id =  _b.GetStreetID();
	
	for(unsigned int i = 0; i < _b.GetStreetSize(); i += 1)
    { 	
    	m_vec[i] = new Building_t<T2>(_b.GetBuildingID(i));
    }
}

template <class T1, class T2> 
const Street_t<T1, T2> & Street_t<T1, T2> :: operator=(Street_t<T1, T2>& _b)
{
	if(this != &_b)
	{
		m_id =  _b.GetStreetID();
		for(unsigned int i = 0; i < _b.GetStreetSize(); i += 1)
    	{ 	
    		m_vec[i] = new Building_t<T2>(_b.GetBuildingID(i));
    	}	
	} 
	return *this;
}

template <class T1, class T2> 
void Street_t<T1, T2> :: SetStreetID(const T1 _id)
{
	m_id = _id;
}

template <class T1, class T2> 
T1& Street_t<T1, T2> :: GetStreetID() const
{
	return m_id;
}

template <class T1, class T2> 
void Street_t<T1, T2> ::AddBuilding(Building_t<T2>& newBuilding)
{
	Building_t<T2>* building= new Building_t<T2>(newBuilding.GetBuildingID());
	m_vec.push_back(building);
}

template <class T1, class T2> 
Building_t<T2>& Street_t<T1, T2> :: GetBuilding(T2& _id)const
{
	typename std::vector<Building_t<T2>*>::iterator it = m_vec.begin();
	
	while((**it).GetBuildingID() != _id)
	{
		++it;
	}
	return (**it); 
}				
				
template <class T1, class T2> 
unsigned int Street_t<T1, T2> :: GetStreetSize()const
{
	return m_vec.size();
}		
		


#endif /* __STREET_H__ */
