#include "Server.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

int NewClient(void* _x, char* _ip, int _ID)
{
	printf("New client ip %s number %d!\n", _ip,_ID);
	return 1;
}

void MyCallBack(void* _server, char* message, size_t size, int _ID)
{
	Server* server = _server;
	char* str = "good morning";
	printf("got message from ID num: %d\n", _ID);
	SendMessage(_server, str, strlen(str) + 1, _ID);
}

int main (int argc, char *argv[])
{
	Server* server;
	ServerData* data = malloc(sizeof(ServerData));
	data->m_context = server;
	data-> m_cbnc = NewClient;
	data->m_cbnm = MyCallBack;
	data->m_port =  atoi(argv[1]);
	data->m_queueSize = atoi(argv[2]);
	data->m_timeOut = 1;

	server = CreateServer(data);
	ServerRoutine(server);
	DestroyServer(server);
	return 0;
}


