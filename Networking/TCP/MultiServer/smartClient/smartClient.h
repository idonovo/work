#ifndef SMART_CLIENT_H
#define SMART_CLIENT_H

#include <stddef.h> /* size_t */
#include "double.h"
#include "list_itr.h"
#include "list_functions.h"

typedef struct SmartClient
{				/* list of client sockets */
	List* m_clients;
	const char* m_ip;
	unsigned int m_port;
	struct sockaddr_in* m_socketAdrr;            
}SmartClient;

typedef struct Client
{
	int m_socket;
	struct sockaddr_in* m_socketAdrr;
} Client;

/*----------------------------------------------------*/

Client* CreateClient();

void ConnectToServer(Client*, const char* _ip, unsigned int m_port);

void CloseConnectToServer(Client*);

void TransferData(Client* _client, const char* _data, unsigned int _length);

void DestroyClient(Client*);

/***************************************/
SmartClient* CreateSmartClient(size_t _NumClients, unsigned int _serverPort, const char* _serverIP);

void DestroySmartClient(SmartClient* _client);

void SmartClientRoutine(SmartClient* _client, unsigned int _numOfLoops);

#endif /* SMART_CLIENT_H */

