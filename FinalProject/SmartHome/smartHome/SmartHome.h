#ifndef __SMARTHOMEH_H__
#define __SMARTHOMEH_H__

#include <string>
#include <tr1/memory>
using namespace std;

class Hub;
class SmartHomeLoader;
class LoggerManager;

class SmartHome
{
	
public:
	virtual ~SmartHome ();
	static SmartHome* CreateSmartHome();
	static SmartHome* sHome;
	virtual void LaunchSmartHome(const std::string& _config);
	 
private:
    SmartHome();
	SmartHome (const SmartHome& arguments);
    SmartHome&operator=(const SmartHome& arguments);
		
private:	
	tr1::shared_ptr<LoggerManager> loggerManager;
	Hub* m_hub;
	tr1::shared_ptr<SmartHomeLoader> m_loader;

};
#endif /* __SMARTHOMEH_H__ */

