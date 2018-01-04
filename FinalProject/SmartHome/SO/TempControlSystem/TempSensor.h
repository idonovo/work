#ifndef __TEMPSENSOR_H__
#define __TEMPSENSOR_H__

#include "Agent.h"

class TempSensor: public Agent
{
public:
    TempSensor(tr1::shared_ptr<AgentData> _data, HubInterface* _hub);
	~TempSensor();
    
    virtual void PushEvent (tr1::shared_ptr<Event> ptr){}	
    virtual bool IsInterested(tr1::shared_ptr<Event> ptr)const {return false;}
    static void* Launch(void* context);
    virtual void SensorRoutine();
    
private:
	TempSensor(const TempSensor& _sensor);
	TempSensor&operator=(const TempSensor& sens);
	void SetMaxMin();
	
private:	 
	 pthread_t threadID;
	 int 	maxTemp;
	 int 	minTemp;
	 int	period;
};


#endif /* __TEMPSENSOR_H__ */

