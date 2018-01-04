#ifndef __SMART_H__
#define __SMART_H__

#include <tr1/memory>
using namespace std;
#include <vector>

class Hub;
class Agent;
class AgentData;
class AgentFactory;
class Parser;
class LoggerManager;
class Logger;

class SmartHomeLoader
{
public:
	SmartHomeLoader(Hub* _hub, tr1::shared_ptr<LoggerManager> _errorsLogger);
	~SmartHomeLoader ();
	
	void LoadObjectTypes(const string& SOfile);
	void InitAgents(const string& conFile);
		
private:		
	SmartHomeLoader (const SmartHomeLoader& arguments);
    SmartHomeLoader&operator=(const SmartHomeLoader& arguments);
    void SetLogger(tr1::shared_ptr<AgentData>& _data);
        
private:
	tr1::shared_ptr<LoggerManager> loggerManager;
	tr1::shared_ptr<AgentFactory> factory;
	tr1::shared_ptr<Parser> parser;
	Hub* hub;	
	vector <Agent*> agentsContainer;
	tr1::shared_ptr<Logger> errorsLogger;
};


#endif /* __SMART_H__ */

