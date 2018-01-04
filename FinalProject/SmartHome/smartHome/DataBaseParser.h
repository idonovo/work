#ifndef __MYPARSERDATABASE_H__
#define __MYPARSERDATABASE_H__

#include "Parser.h"

class DataBaseParser: public Parser
{
public:
	DataBaseParser (DB_info info;);
	virtual ~DataBaseParser ();
	
	virtual tr1::shared_ptr<AgentData> GetNextAgentData();
	
private:
	tr1::shared_ptr<DataBase>  m_DB;

};

#endif /* __MYPARSERDATABASE_H__ */

