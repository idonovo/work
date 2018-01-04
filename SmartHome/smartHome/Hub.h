#ifndef __HUB_H__
#define __HUB_H__

#include "IHub.h"
#include "ProtectedQueue.h"
#include <pthread.h>
#include <tr1/memory>
#include <string>
#include <vector>

class AgentEventsHandler;
class Agent;
class Event;
class Logger;

class Hub: public HubInterface
{
public:	
    
    Hub(tr1::shared_ptr<Logger> _errorsLogger);
	virtual	~Hub ();
	
	static void* Lounch(void* _context);
	
	virtual void Subscribe(Agent* agent);
	virtual bool ReleaseAgent(const std::string& _ID);
	virtual void PushEvent(tr1::shared_ptr<Event> ptr);
	virtual bool IsExist(const std::string& _ID);
	virtual void Routine();
	 
private:
	Hub (const Hub& _hb);
    Hub&operator=(const Hub& _hub);
	const Agent* FindAgent(const string& _ID);
	
private:
	tr1::shared_ptr<Logger> errorsLogger;
	vector<AgentEventsHandler*> handlersContainer; 
	pthread_mutex_t m_mutex;
	pthread_t m_threadID;
	ProtectedQueue< tr1::shared_ptr<Event> > m_eventsQueue;
};


#endif /* __HUB_H__ */

