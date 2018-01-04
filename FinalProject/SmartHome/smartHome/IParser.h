#ifndef __IPARSER_H__
#define __IPARSER_H__

#include <tr1/memory>
using namespace std;
class AgentData;

template<class T>
class IParser
{
public:
	IParser (const T& _obj):m_config(_obj){}
	virtual ~IParser ();
	
	virtual tr1::shared_ptr<AgentData> GetNextAgentData() = 0;

protected:
	T& m_config;
};



#endif /* __IPARSER_H__ */

