#include "Server.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

int NewClient(void* _x, int _ID)
{
	printf("New client number %d!\n", _ID);
	return 1;
}

void MyCallBack(void* _server, char* message, size_t size, int _ID)
{
	Server* server = _server;
	char* str = "good morning";
	printf("got message from ID num: %d\n", _ID);
	SendMessage(str, strlen(str) + 1, _ID);
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

	server = CreateServer(data);
	ServerRoutin(server);
	DestroyServer(server);
	return 0;
}


