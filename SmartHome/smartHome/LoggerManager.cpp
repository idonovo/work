
#include "LoggerManager.h"

LoggerManager::LoggerManager()
{
	tr1::shared_ptr<Logger> newLogger1(new Logger("DefLogger"));
	m_loggersMap.insert(std::pair<string,tr1::shared_ptr<Logger> > ("DefLogger", newLogger1));
	tr1::shared_ptr<Logger> newLogger2(new Logger("ErrorLogger"));
	m_loggersMap.insert(std::pair<string,tr1::shared_ptr<Logger> > ("ErrorLogger", newLogger2));
}

tr1::shared_ptr<Logger> LoggerManager::GetLogger(const string& _logName)
{
	 
    map<string, tr1::shared_ptr<Logger> >::iterator it = m_loggersMap.find(_logName);
    if(it ==  m_loggersMap.end())
	{
		tr1::shared_ptr<Logger> newLogger(new Logger(_logName));
		m_loggersMap.insert(std::pair<string,tr1::shared_ptr<Logger> > (_logName, newLogger));
		return newLogger;
	}
	return ((it)->second);
}

tr1::shared_ptr<Logger> LoggerManager::GetDefaultLogger()
{
	map<string, tr1::shared_ptr<Logger> >::iterator it = m_loggersMap.find("DefLogger");
	return ((it)->second);
}

tr1::shared_ptr<Logger> LoggerManager::GetErrorsLogger()
{
	map<string, tr1::shared_ptr<Logger> >::iterator it = m_loggersMap.find("ErrorLogger");
	return ((it)->second);
}
