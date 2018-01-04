#ifndef AGENT_H
#define AGENT_H

#include <tr1/memory>
#include <string>
#include <iostream>

using namespace std;
#include "AgentData.h"
#include "Event.h"
#include "IHub.h"

/**
  * class Agent
  * 
  */

class Event;

class Agent
{
public:

	Agent(tr1::shared_ptr<AgentData> _data, HubInterface* _hub):m_hub(_hub), m_data(_data){}
	virtual ~Agent (){}
	virtual void PushEvent (tr1::shared_ptr<Event> ptr)=0;
	virtual bool IsInterested (tr1::shared_ptr<Event> ptr) const = 0;
	void PublishEvent (tr1::shared_ptr<Event> ptr){m_hub->PushEvent(ptr);}
	const string& GetType()const{return m_data->m_type;}
	const string& GetID()const {return m_data->m_ID;}

private:
  	Agent& operator= (const Agent& agent);
	Agent (const Agent& agent);
	
protected:
	HubInterface* m_hub;
	tr1::shared_ptr<AgentData> m_data;

};

#endif // AGENT_H
