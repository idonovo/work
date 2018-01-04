#include "SmartHome.h"
#include "Logger.h"

#include <iostream>


int main (int argc, char const* argv[])
{

	
	SmartHome* sh = SmartHome::CreateSmartHome();
	std::cout<< std::endl<< std::endl << "please choose 1 for FireSystem simulation or 0 for TempretureControlSystem" << std::endl;
	int  choice;
	std::cin >> choice;  
	if(choice == 1)
	{
		sh->LaunchSmartHome("config.txt");
	}
	
	if(choice == 0)
	{
		sh->LaunchSmartHome("TempControlConfig.txt");
	}
	
}


