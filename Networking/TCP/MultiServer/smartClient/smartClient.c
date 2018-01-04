#include <stdlib.h>
#include <sys/types.h> /* sockets */
#include <sys/socket.h> /* sockets */
#include <netinet/in.h> /* struct sockaddr_in */
#include <unistd.h> /* close */
#include <stdio.h> /* perror */
#include <arpa/inet.h> /* inet_addr */
#include <errno.h>
#include <string.h>

#include "smartClient.h"

#define MIN_PORT 1100
#define MAX_PORT 65535

/*****************************Client******************************************/
/********************************************************/
static int MakeSocket(void);
/*********************************************************/
Client* CreateClient()
{
	Client* client = malloc(sizeof(Client));
	if(!client)
	{
		return NULL;
	}
	client->m_socketAdrr =  malloc(sizeof(struct sockaddr_in));
	return client;
	
}

static int MakeSocket(void)
{
	int socketFD;
	socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0) 
    {    
		perror("socket error");
    }
    
    return socketFD;
}

void ConnectToServer(Client* _client, const char* _ip, unsigned int _port)
{
	_client->m_socket = MakeSocket();
	memset(_client-> m_socketAdrr, 0, sizeof(struct sockaddr_in));
 	_client-> m_socketAdrr->sin_family = AF_INET;
 	_client-> m_socketAdrr->sin_addr.s_addr = inet_addr(_ip);
 	_client-> m_socketAdrr->sin_port = htons(_port); 
 	if(0 > connect(_client->m_socket, (struct sockaddr*)_client-> m_socketAdrr, sizeof(struct sockaddr_in)))
	{    
		perror("connect error");
		return;
    } 
    return;
}

void CloseConnectToServer(Client* _client)
{
	close(_client->m_socket);
}

void TransferData(Client* _client, const char* _data, unsigned int _length)
{
	int count;
	char buf[512];

 	count = send(_client->m_socket, _data, _length, 0);
 	if(count < 0)
 	{
		perror("recvfrom error");
 	}
 	if(count == 0)
 	{
		perror("server overflow");
 	}
 		 	
	count = recv(_client->m_socket, buf, sizeof(buf)-1, 0);
	printf("%d\n", count);
 	if(count < 0)
 	{
		perror("recv error");
 	}
 	
 	buf[count] = '\0';	
 	printf("%s\n", buf); 

}

void DestroyClient(Client* _client)
{
	free(_client->m_socketAdrr);
	free(_client);
}

/*****************************Smart Client******************************************/
static struct sockaddr_in* CreateSocketAddr(unsigned int _port, const char* _ip);
static size_t CreateClients(List* _listToFill, size_t _NumClients);
static void DestroyClientAddr(struct sockaddr_in* _addr);
/***************************************************************************************/
SmartClient* CreateSmartClient(size_t _NumClients, unsigned int _serverPort, const char* _serverIP)
{
	SmartClient* newSmartClient;
	
	newSmartClient = malloc(sizeof(SmartClient));
	if(NULL == newSmartClient)
	{
		return NULL;
	}
	newSmartClient->m_ip = _serverIP;
	newSmartClient->m_port = _serverPort;
	newSmartClient->m_socketAdrr = CreateSocketAddr(_serverPort, _serverIP);
	if(NULL == newSmartClient->m_socketAdrr)
	{
		free(newSmartClient);
		return NULL;
	}
	
	newSmartClient->m_clients = ListCreate();
	if(NULL == newSmartClient->m_clients)
	{
		free(newSmartClient->m_socketAdrr);
		free(newSmartClient);
		return NULL;
	}
	
	CreateClients(newSmartClient->m_clients, _NumClients);
	
	return newSmartClient;
}

static struct sockaddr_in* CreateSocketAddr(unsigned int _port, const char* _ip)
{
	struct sockaddr_in* newAddress;
	
	if(MIN_PORT > _port || MAX_PORT < _port)
	{
		return NULL;
	}
	
	newAddress = calloc(1, sizeof(struct sockaddr_in));
	if(NULL == newAddress)
	{
		return NULL;
	}
	newAddress->sin_family = AF_INET;
    newAddress->sin_port = htons(_port);
    newAddress->sin_addr.s_addr = inet_addr(_ip);
    
    return newAddress;
}

static void DestroyClientAddr(struct sockaddr_in* _addr)
{
	free(_addr);
}


static size_t CreateClients(List* _listToFill, size_t _NumClients)
{
	size_t i;
	Client* clientPtr;
	for(i = 0; i < _NumClients; ++i)
	{
		clientPtr = CreateClient();
		if(clientPtr)
		{
			ListPushTail(_listToFill, clientPtr);
		}
	}
	return i;
}

void DestroySmartClient(SmartClient* _client)
{
	ListDestroy(&_client->m_clients, (UserActionFunc)DestroyClient);
	free(_client->m_socketAdrr);
	free(_client);
}

void SmartClientRoutine(SmartClient* _client, unsigned int _numOfLoops)
{
	char* message = "i am a client";
    int res, i, length = strlen(message) +1;
	ListItr begin = ListItr_Begin(_client->m_clients);
    ListItr end =  ListItr_End(_client->m_clients);
	
	for (i = 0; i < _numOfLoops; i += 1)
	{	
		while(begin != end)
		{
			Client* ptr = ListItr_Get(begin);
			res = rand() % 100 + 1;
		
			if(res < 70)
			{
				 ConnectToServer(ptr, _client->m_ip, _client->m_port);
				 TransferData(ptr, message,length);
				 sleep(2);
				 CloseConnectToServer(ptr);
			}
			else
			{
				ConnectToServer(ptr, _client->m_ip, _client->m_port);
				CloseConnectToServer(ptr);
			}
		 	begin = ListItr_Next(begin);
		}
	}
	
}



