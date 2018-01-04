#include "Logger.h"

Logger::Logger(const std::string& _fileName)		
{
	m_fileName = "./Loggers/" + _fileName + ".txt";
	m_stream.open(m_fileName.c_str(), std::ios::out | std::ios::app);
	
	pthread_mutex_init(&m_mutex, 0);
}


Logger::Logger(const Logger& _log)
{
	m_fileName = _log.m_fileName;
	m_stream.open(m_fileName.c_str(), std::ios::out | std::ios::app);
	pthread_mutex_init(&m_mutex, 0);
	
}

Logger& Logger::operator=(const Logger& _log)
{
	if(this != &_log)
	{
		m_fileName = _log.m_fileName;
		if(m_stream)
		{	
			m_stream.close();
		}
		m_stream.open(m_fileName.c_str(), std::ios::out | std::ios::app);
	}
	return *this;
}

Logger::~Logger ()
{
	m_stream.close();
	pthread_mutex_destroy(&m_mutex);
}

void Logger::Write(const std::string& _line, const std::string& _ID)
{
	Guard guard(&m_mutex);
	time_t now = time(0);
    tm* localtm = localtime(&now);
	m_stream << asctime(localtm) << " |Agnet ID: " << _ID << " |Desc.: " << _line << std::endl;
}

Logger& Logger:: operator <<(const std::string& _line)
{
	Guard guard(&m_mutex);
	time_t now = time(0);
    tm* localtm = localtime(&now);
	m_stream << asctime(localtm) << " |Desc.: " << _line << std::endl;
	return *this;
}

