#ifndef __IHUB_H__
#define __IHUB_H__

#include <tr1/memory>
using namespace std;
#include<string>

class Agent;
class Event;

class HubInterface
{
public:

    virtual ~HubInterface (){}
    virtual void Subscribe(Agent* agent)=0;
	virtual bool ReleaseAgent(const std::string& _ID)=0;
	virtual void PushEvent(tr1::shared_ptr<Event> ptr)=0;
	virtual bool IsExist(const std::string& _ID)=0; 
     
};
#endif /* __IHUB_H__ */

