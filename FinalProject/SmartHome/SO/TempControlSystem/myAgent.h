
#ifndef __MYAGENT_H__
#define __MYAGENT_H__

#include "Agent.h"
#include "TempSensPayload.h"
#include <sstream> 


class TempScreen: public Agent
{
public:
	TempScreen(tr1::shared_ptr<AgentData> _data, HubInterface* _hub): Agent(_data, _hub)
	{
		m_hub->Subscribe(this);
	}
	virtual ~TempScreen (){}

private:
    TempScreen&operator=(const TempScreen& arguments);
	TempScreen(const TempScreen& arguments);

public: 
    
    virtual void PushEvent (tr1::shared_ptr<Event> ptr)
    {
		std::stringstream ss;
		ss << "The tempreture at floor" << ptr->GetFloor() << (string)"is: " << ((TempSensPayload*)ptr->GetPayload())->strCurTemp << endl;
		m_data->m_logger->Write(ss.str(),m_data->m_ID);
	}
		
    virtual bool IsInterested(tr1::shared_ptr<Event> ptr)const{return true;}
    
};

#endif /* __MYAGENT_H__ */

