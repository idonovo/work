#ifndef __CREATOR_H__
#define __CREATOR_H__

#include <tr1/memory>
#include <map>
#include<iostream>
using namespace std;

class HubInterface;
class AgentData;
class Agent;

extern "C" void* AgentCreate(tr1::shared_ptr<AgentData> data, const string& type, HubInterface* _hub);

extern "C" void GetAgentType(map<string,string>& map);

#endif /* __CREATOR_H__ */


