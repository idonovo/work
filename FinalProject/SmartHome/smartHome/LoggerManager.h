#ifndef __LOGGERMANAGER_H__
#define __LOGGERMANAGER_H__

#include <map>
#include <tr1/memory>
using namespace std;
#include "Logger.h"

class LoggerManager
{
public:
    LoggerManager();
	~LoggerManager (){}
	
   	tr1::shared_ptr<Logger> GetLogger(const string& _logName);
   	tr1::shared_ptr<Logger> GetDefaultLogger();
   	tr1::shared_ptr<Logger> GetErrorsLogger();
    
private:
	LoggerManager (const LoggerManager& arguments);
    LoggerManager&operator=(const LoggerManager& arguments);

private:
	map<string,tr1::shared_ptr<Logger> > m_loggersMap;/*map of all loggers name (key) and loggers objects */
};


#endif /* __LOGGERMANAGER_H__ */


