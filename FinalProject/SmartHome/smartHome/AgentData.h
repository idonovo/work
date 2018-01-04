#ifndef __AGENTDATA_H__
#define __AGENTDATA_H__

#include <tr1/memory>
#include <string>
using namespace std;
#include "Logger.h"

class AgentData
{
public:
    AgentData(){}
	AgentData (const AgentData& _data);
	virtual ~AgentData (){};
    AgentData&operator=(const AgentData& _data);
    
    std::string m_ID;
    std::string m_type;
    std::string m_log;
    std::string	m_config;
    std::string	m_floor;
    std::string	m_room;
	tr1::shared_ptr<Logger> m_logger;
};

#endif /* __AGENTDATA_H__ */

