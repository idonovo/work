#ifndef __HANDLER_H__
#define __HANDLER_H__

#include "ProtectedQueue.h"
#include <pthread.h>
#include <tr1/memory>
using namespace std;
class Event;
class Hub;
class Agent;

class AgentEventsHandler
{
public:
    AgentEventsHandler (Agent* _agent);
    virtual ~AgentEventsHandler ();
    
    static void* Launch(void* context);
    
    virtual void CheckForEvents();
    const string& GetID()const;
    const Agent* GetAgent()const;
    bool IsInterested(tr1::shared_ptr<Event> ptr) const;
    void PushEvent(tr1::shared_ptr<Event> ptr);

private:
	AgentEventsHandler(const AgentEventsHandler& _agent);
	AgentEventsHandler& operator=(AgentEventsHandler& agent);
	
private:
    Agent* m_agent;
    pthread_t m_threadID;
    ProtectedQueue< tr1::shared_ptr<Event> > m_queue; 
};


#endif /* __HANDLER_H__ */

