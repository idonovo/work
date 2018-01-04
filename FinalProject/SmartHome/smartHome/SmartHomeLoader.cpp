#include "SmartHomeLoader.h"
#include "Hub.h"
#include "Parser.h"
#include "AgentFactory.h"
#include "Agent.h"
#include "LoggerManager.h"
#include "Logger.h"
#include <sstream>



SmartHomeLoader::SmartHomeLoader(Hub* _hub, tr1::shared_ptr<LoggerManager> _loggerManager): loggerManager (_loggerManager), factory(new AgentFactory), parser(new Parser<int>), hub(_hub)
{
	errorsLogger = loggerManager->GetErrorsLogger();
}
SmartHomeLoader::~SmartHomeLoader (){}

void SmartHomeLoader::LoadObjectTypes(const string& _dirPath)
{
	if(_dirPath.empty())
	{
		std::stringstream ss;
		ss << "in" << __FILE__  << "line: " << __LINE__ << " empty filename";
		*errorsLogger << ss.str();
		throw "empty string file name";
	}
	try
	{
		factory->MapDir(_dirPath);
	}
	catch(string str)
	{
		if(str == "file cannot open")
		{
			std::stringstream ss;
			ss << "in" << __FILE__  << "line: " << __LINE__ << " empty filename";
			*errorsLogger << ss.str();
			throw "empty string file name";
		}
	}
	return;
}

void SmartHomeLoader::InitAgents(const string& conFile)
{
	
	if(conFile.empty())
	{
		std::stringstream ss;
		ss << "in" << __FILE__  << "line: " << __LINE__ << " empty filename";
		*errorsLogger << ss.str();
		throw "empty string file name";
	}
	
	parser->GetConfig<const string&>(conFile);
	while(1)
	{
		try
		{				
			tr1::shared_ptr<AgentData> data = parser->GetNextAgentData();
			SetLogger(data);
			Agent* newAgent = factory->CreateAgent(data, data->m_type, hub);
			agentsContainer.push_back(newAgent); 
		}
		catch(string str)
		{
			*errorsLogger << str;
			if(str == "end of file")
			{
				return;
			}
		}
	} 
}

void SmartHomeLoader::SetLogger(tr1::shared_ptr<AgentData>& _data)
{
	if(_data->m_log.empty())
	{
		_data->m_logger = loggerManager->GetDefaultLogger();
	}
	else
	{
		_data->m_logger = loggerManager->GetLogger(_data->m_log);
	}
}


