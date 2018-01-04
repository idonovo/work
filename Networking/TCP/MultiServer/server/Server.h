#ifndef __SERVER_H__
#define __SERVER_H__

#include "double.h"
#include "list_itr.h"
#include "list_functions.h"

typedef struct ClientData ClientData;


typedef int (*CallBackNewClient)(void*, int);

typedef void (*CallBackNewMessage)(void*, char* _Resivemsg, size_t size, int _ID);

typedef struct ServerData
{
	void* m_context;
	CallBackNewClient m_cbnc;
	CallBackNewMessage m_cbnm;
	size_t m_port;
	size_t m_queueSize;
} ServerData;

typedef struct Server Server;

Server* CreateServer(ServerData*);

void ServerRoutin(Server* _server);

int SendMessage(char* _message, size_t _length, int _ID);

void DestroyServer(Server* _server);


#endif /* __SERVER_H */

