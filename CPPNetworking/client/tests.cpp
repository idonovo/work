#include "SocketConnector.h"
#include "SocketStream.h"
#include "Socket.h"
#include <unistd.h>
#include <string.h>

using namespace  Netcpp;

int main (int argc, char const* argv[])
{
	std::string str("127.0.0.1");
	Peer_info info(2224, str);
	
	SocketConnector connector;
	sleep(1);
	std::tr1::shared_ptr<Socket> ptr(connector.Connect(info));
	char* msg = "message";
	std::tr1::shared_ptr<SocketStream> stream(new SocketStream(msg, strlen(msg)+1));
	for (unsigned int i = 0; i < 1; i += 1)
	{
		sleep(1);
		ptr->Send(stream);
	}
	return 0;
}

