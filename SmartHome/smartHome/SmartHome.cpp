#include "SmartHome.h"
#include "LoggerManager.h"
#include "Hub.h"
#include "SmartHomeLoader.h"
#include <iostream>

SmartHome* SmartHome:: sHome = 0;

SmartHome* SmartHome:: CreateSmartHome()
{
	if(!sHome)
	{
		sHome = new SmartHome;
	}
	return sHome;
}

SmartHome::SmartHome():
loggerManager(new LoggerManager),
 m_hub(new Hub(loggerManager->GetErrorsLogger())), 
 m_loader(new SmartHomeLoader(m_hub, loggerManager))
 {}

SmartHome::~SmartHome(){}

void SmartHome::LaunchSmartHome(const string& _config)
{
	m_loader->LoadObjectTypes("../SOS/");
	m_loader->InitAgents(_config);
	int input;
	std::cout<< std::endl<< std::endl << "is running... please press any key to stop";
	std::cin >> input;
	std::cout << "end!!..." << std::endl<< std::endl;
	
}

