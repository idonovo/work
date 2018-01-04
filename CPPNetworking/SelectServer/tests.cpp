#include <iostream>
#include "SelectServer.h"
#include "Application.h"


using namespace  Netcpp;

int main (int argc, char const* argv[])
{
	std::tr1::shared_ptr<Application> ap(new Application);;
	std::string str("127.0.0.1");
	Peer_info info(2224, str);
	SelectServer<Application> server(info, ap,100);
	return 0;
}

