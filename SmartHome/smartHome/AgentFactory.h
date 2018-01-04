#ifndef __FACTORY_H__
#define __FACTORY_H__

#include <tr1/memory>
#include <map>
using namespace std;

class HubInterface;
class AgentData;
class Agent;

class AgentFactory
{

public:
    AgentFactory(){}	
	virtual ~AgentFactory (){}
    virtual Agent* CreateAgent(tr1::shared_ptr<AgentData> data, const string& type, HubInterface* _hub);
	void MapDir(const string& _path);	
		
	private:
    AgentFactory&operator=(const AgentFactory& arguments);
    AgentFactory(const AgentFactory& arguments);
    
    virtual bool MapSO(const string& SOfile);
    
private:
	
	std::map <string, string> m_typesAndFiles; /* map of types and object files */
};
#endif /* __FACTORY_H__ */

