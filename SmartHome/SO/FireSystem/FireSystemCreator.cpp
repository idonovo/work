#include <pthread.h>
#include "AgentCreator.h"
#include "Fire.h"
#include "Sprinkler.h"


void* AgentCreate(tr1::shared_ptr<AgentData> data, const string& type, HubInterface* _hub)
{
	if(type == "FireDetector")
	{	
		FireDetector* agent  = new FireDetector(data, _hub);
		return (void*) agent;
	}
	
	if(type == "Sprinkler")
	{
		Sprinkler* agent  = new Sprinkler(data, _hub);
		return (void*) agent;
	} 
	FireDetector* agent  = new FireDetector(data, _hub);
	return agent;
}

void GetAgentType(map <string, string>& types)
{
	types.insert(std::pair<string,string>("FireDetector", "../SOS/FireSystemCreator.so"));
	types.insert(std::pair<string,string>("Sprinkler", "../SOS/FireSystemCreator.so"));
}

