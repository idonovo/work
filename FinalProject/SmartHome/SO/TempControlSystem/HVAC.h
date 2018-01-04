

#include "Agent.h"

class HVAC: public Agent{
public:
    HVAC(tr1::shared_ptr<AgentData> _data, HubInterface* _hub);
	~HVAC (){}

    virtual void PushEvent (tr1::shared_ptr<Event> ptr);	
    virtual  bool IsInterested(tr1::shared_ptr<Event> ptr)const;
    
private:	  
	HVAC (const HVAC& _arguments);
    HVAC&operator=(const HVAC& _arguments);
    void SetMaxMin();
    
    
private:
	int maxTemp;
	int minTemp;
};

