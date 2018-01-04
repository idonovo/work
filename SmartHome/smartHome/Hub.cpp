#include <sstream>
#include "Hub.h"
#include "AgentEventsHandler.h"
#include "Agent.h"
#include "Guard.h"
#include "Logger.h"

Hub::Hub(tr1::shared_ptr<Logger> _errorsLogger):  errorsLogger(_errorsLogger)
{
    pthread_mutex_init(&m_mutex, 0);
    if (0 != pthread_create(&m_threadID, NULL, Hub::Lounch, (void*)this))
	{
    	throw "thread create fail"; 
	}
}

void* Hub::Lounch(void* _context)
{
	((Hub*)_context)->Routine();
	return _context;
}

void Hub::Routine()
{
	for(;;)
    {
        tr1::shared_ptr<Event>ptr;
        m_eventsQueue.Remove(&ptr);
        for (vector<AgentEventsHandler*>:: iterator it = handlersContainer.begin(); it != handlersContainer.end(); ++it)
		{
			if((*(it))->IsInterested(ptr))
			{
				(*(it))->PushEvent(ptr);
			}
		}
    }
}

void Hub::Subscribe(Agent* agent)
{
	if(!agent)
	{
		std::stringstream ss;
		ss << "in" << __FILE__  << "line: " << __LINE__ << "Agent not init";
		*errorsLogger << ss.str();
	}
	
	if(IsExist(agent->GetID()))
	{
		std::stringstream ss;
		ss << "in" << __FILE__  << "line: " << __LINE__ << "Agent allready exist";
		*errorsLogger << ss.str();
	}
	
	try
	{
		AgentEventsHandler* handler = new AgentEventsHandler(agent);
		Guard guard(&m_mutex);
		handlersContainer.push_back(handler);	
	}
	catch(std::string str)
	{
		std::stringstream ss;
		ss << "in" << __FILE__  << "line: " << __LINE__ << "Agent " << agent->GetID() << "handler create fail";
		*errorsLogger << ss.str();
	}
}

bool Hub::ReleaseAgent(const string& _ID)
{
	Guard guard(&m_mutex);
	if(IsExist(_ID))
	{
		delete FindAgent(_ID);
		return true;
	}
	return false;
}

void Hub::PushEvent(tr1::shared_ptr<Event> ptr)
{
	m_eventsQueue.Insert(ptr);
}

bool Hub::IsExist(const string& _ID)
{
	return FindAgent(_ID)? true: false;
} 

const Agent* Hub::FindAgent(const string& _ID)
{
	for (vector<AgentEventsHandler*>:: iterator it = handlersContainer.begin(); it != handlersContainer.end(); ++it)
	{
		if(_ID == (*it)->GetID())
		{
			return (*it)->GetAgent();
		}
	}
	return 0;
}

Hub::~Hub ()
{
	for (vector<AgentEventsHandler*>:: iterator it = handlersContainer.end(); it == handlersContainer.begin(); --it)
	{
		delete *(handlersContainer.erase(it));
	}
    pthread_mutex_destroy(&m_mutex);
    pthread_join(m_threadID, NULL);
    
}
