#include <pthread.h>
#include "AgentCreator.h"
#include "myAgent.h"
#include "TempSensor.h"
#include "HVAC.h"


void* AgentCreate(tr1::shared_ptr<AgentData> data, const string& type, HubInterface* _hub)
{
	if(type == "MyAgent")
	{	
		TempScreen* agent  = new TempScreen(data, _hub);
		return (void*) agent;
	}
	
	if(type == "TempSensor")
	{
		TempSensor* agent  = new TempSensor(data, _hub);
		return (void*) agent;
	}
	
	if(type == "HVAC")
	{
		HVAC* agent  = new HVAC(data, _hub);
		return (void*) agent;
	}

	TempScreen* agent  = new TempScreen(data, _hub);
	return agent;
}

void GetAgentType(map <string, string>& types)
{
	types.insert(std::pair<string,string>("TempScreen", "../SOS/TempControlSystem.so"));
	types.insert(std::pair<string,string>("TempSensor", "../SOS/TempControlSystem.so"));
	types.insert(std::pair<string,string>("HVAC", "../SOS/TempControlSystem.so"));
}


