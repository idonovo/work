#ifndef __BUILDING_H__
#define __BUILDING_H__


template <class T> 
class Building_t
{

public:
	Building_t(T& _id);
	virtual ~Building_t();
	Building_t(const Building_t& _b);  
	const Building_t& operator=(Building_t& _b);
	
	void 		SetBuidingID(const T _id);	
	T&			GetBuildingID();
	
private:
	T m_data;
}; 

template <class T> 
Building_t<T>:: Building_t(T& _id)
{
	m_data = _id;
}

template <class T> 
Building_t<T>:: ~Building_t(){}

template <class T> 
Building_t<T>::Building_t(const Building_t& _b)
{
	m_data =  _b.GetBuildingID();
} 

template <class T> 
const Building_t<T>& Building_t<T>::operator=(Building_t& _b)
{
	if(this != &_b)
	{
		m_data = _b.GetBuildingID();
	} 
	return *this;
}

template <class T> 
void Building_t<T>::SetBuidingID(const T _id)
{
	m_data = _id;
}

template <class T> 	
T&	Building_t<T>::GetBuildingID()
{
	return m_data;
}


#endif /* __BUILDING_H__ */


