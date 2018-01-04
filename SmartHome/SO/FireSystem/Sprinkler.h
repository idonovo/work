#ifndef __SPRINKLER_H__
#define __SPRINKLER_H__

#include "Agent.h"
#include <sstream> 

class Sprinkler: public Agent
{

public:

	Sprinkler (tr1::shared_ptr<AgentData> _data, HubInterface* _hub): Agent(_data, _hub)
	{
		m_hub->Subscribe(this);
	}
	~Sprinkler (){};
    
    virtual void PushEvent (tr1::shared_ptr<Event> ptr)
    {
		if(ptr->GetType() == "Fire detected")
		{
		    std::stringstream ss;
			ss << "Fire detected at floor number :" << ptr->GetFloor() << "sprinkler " << m_data-> m_ID << "is on! "<< endl;
		    m_data->m_logger->Write(ss.str(),m_data->m_ID);
		}
		
		if(ptr->GetType() == "Fire Off")
		{
		    std::stringstream ss;
			ss << "Fire at floor number :" << ptr->GetFloor() << " is Off. sprinkler " << m_data-> m_ID << "is off! "<< endl;
		    m_data->m_logger->Write(ss.str(),m_data->m_ID);
		}
	}
		
    virtual bool IsInterested(tr1::shared_ptr<Event> ptr)const
    {
    	return (ptr->GetFloor() == m_data->m_floor && ptr->GetType() == "Fire detected") || (ptr->GetFloor() == m_data->m_floor && ptr->GetType() == "Fire Off")? true : false;
    }
    
    
private:
	Sprinkler (const Sprinkler& arguments);
    Sprinkler&operator=(const Sprinkler& arguments);

};


#endif /* __SPRINKLER_H__ */

