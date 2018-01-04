
#ifndef __Fire_H__
#define __Fire_H__

#include <stdlib.h>   
#include <sstream> 
#include <pthread.h>
#include <unistd.h>
using namespace std;

#include "IHub.h"
#include "Agent.h"

class FireDetector: public Agent
{

public:
	FireDetector(tr1::shared_ptr<AgentData> _data, HubInterface* _hub): Agent(_data, _hub)
	{
		if (0 != pthread_create(&threadID, NULL, FireDetector::Launch, (void*)this))
		{
			throw "thread create fail"; 
		}
	}
	virtual ~FireDetector ()
	{
		 pthread_join(threadID, 0);
	}


public: 
    virtual void PushEvent (tr1::shared_ptr<Event> ptr){}
    virtual bool IsInterested(tr1::shared_ptr<Event> ptr)const{return false;}
    
    
    static void* Launch(void* context)
    {
    	
    	((FireDetector*)context)->FireRoutine();
    	return context;
    }
    
    virtual void FireRoutine()
    {
        while(1)
    	{
			sleep(2);
			std::stringstream ss;
			ss << "Fire detected on floor number" << m_data->m_floor << endl;
			m_data->m_logger->Write(ss.str(), m_data->m_ID);
    		tr1::shared_ptr<Event> ptr1 (new Event("Fire detected",m_data->m_floor, "1"));
			PublishEvent(ptr1);
			
			sleep(4);
			std::stringstream ss1;
			ss1 << "Fire off on floor number" << m_data->m_floor << endl;
			m_data->m_logger->Write(ss1.str(), m_data->m_ID);
    		tr1::shared_ptr<Event> ptr2 (new Event("Fire Off", m_data->m_floor, "1"));
			PublishEvent(ptr2);
    	}
    } 
      
private:
    FireDetector&operator=(const FireDetector& arguments);
	FireDetector(const FireDetector& arguments);
	
private:
	pthread_t threadID;
};



#endif /* __Fire_H__ */

