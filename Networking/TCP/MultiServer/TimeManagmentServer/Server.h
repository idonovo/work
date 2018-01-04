#ifndef __SERVER_H__
#define __SERVER_H__

#include "double.h"
#include "list_itr.h"
#include "list_functions.h"


typedef int (*CallBackNewClient)(void*, char*, int);

typedef void (*CallBackNewMessage)(void*, char* _Resivemsg, size_t size, int _ID);

typedef struct ServerData /*public struct with required information from user(application). */
{
	void* m_context;
	CallBackNewClient m_cbnc;
	CallBackNewMessage m_cbnm;
	size_t m_port;
	size_t m_queueSize;
	size_t m_timeOut;
} ServerData;

typedef struct Server Server;

typedef struct ClientData ClientData;

Server* CreateServer(ServerData*);

void ServerRoutine(Server*);

int SendMessage(Server* _server, char* _message, size_t _size, int _ID);

int DisconnectClient(Server*, int _ID);

void DestroyServer(Server*);


#endif /* __SERVER_H */

