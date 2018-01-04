#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>   
#include "AgentEventsHandler.h"
#include "Agent.h"
#include "Hub.h"

AgentEventsHandler::AgentEventsHandler (Agent* _agent)
{
    if(!_agent)
    {
    	throw "agent not init";
    }

    m_agent = _agent;  
      
	if (0 != pthread_create(&m_threadID, NULL, AgentEventsHandler::Launch, (void*)this))
	{
    	throw "thread create fail"; 
	}
}
 
AgentEventsHandler::~AgentEventsHandler ()
{
 	delete m_agent;
	pthread_join(m_threadID, NULL);
}
    
void* AgentEventsHandler::Launch(void* context)
{

    ((AgentEventsHandler*)context)->CheckForEvents();
    return context;
}

void AgentEventsHandler::CheckForEvents()
{
    for(;;)
    {
        tr1::shared_ptr<Event>ptr;
        m_queue.Remove(&ptr);
        m_agent->PushEvent(ptr);
    }
}

const string& AgentEventsHandler::GetID()const
{
	return m_agent->GetID();
}

const Agent* AgentEventsHandler::GetAgent()const
{
	return m_agent;
}

bool AgentEventsHandler::IsInterested(tr1::shared_ptr<Event>ptr) const
{
	return m_agent-> IsInterested(ptr);
}

void AgentEventsHandler::PushEvent(tr1::shared_ptr<Event>ptr)
{
    m_queue.Insert(ptr);
}
