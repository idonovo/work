#ifndef __LOGGERMY_H__
#define __LOGGERMY_H__

#include <string>
#include <fstream>  
#include <pthread.h>
#include "Guard.h"

class Logger
{
public:
	Logger(const std::string& _fileName);
	~Logger ();
	
	Logger& operator<<(const std::string&);
	void Write(const std::string& _line, const std::string& _ID);
	
private:
	Logger (const Logger& _log);
   	Logger&operator=(const Logger& _log);

private:
	 std::string m_fileName;
	 std::ofstream m_stream;
	 pthread_mutex_t m_mutex;
};
#endif /* __LOGGERMY_H__ */

