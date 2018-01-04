#include "Server.h"
#include <stdlib.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define FAIL -1

struct ClientData 
{
    int m_socket;
};

struct Server 
{
    List* m_clientsData;
    int m_serverSocket;
    struct sockaddr_in* m_sin;
   	CallBackNewMessage m_callBackNewMessage;
    CallBackNewClient m_callBackNewClient;
    void* m_applicationContext;
};
/******************************************************************************************************/
static int DestroyClientData(void*, void*);
static int MakeSocket(void);
static int InitTCPServer(struct sockaddr_in* _sockaddr, size_t _port, int _socketFD, size_t _queueSize);
static int CheckNewClients(Server* _server);
static int CheckError(void);
static void InsertNewClient(int _socket, List* _list);
static int CheckCurrentClients(Server* _server);
static void HandleNewMessage(Server* _server, int _socket, void* _buf, ssize_t _count);
static void ResetClient(ListItr _itr);
static int ConvertToNonBlockedSocket(int socketFD);
/******************************************************************************************************/

Server* CreateServer(ServerData* _data)
{

	Server* server;
	
	if(!_data || !_data->m_cbnm)
	{
		return NULL;
	}
	
	server = malloc(sizeof(Server));
	if(!server)
	{
		return NULL;
	}
	
	server->m_callBackNewMessage = _data->m_cbnm;
	server->m_callBackNewClient = _data->m_cbnc;
	server->m_clientsData = ListCreate();
	if(!server->m_clientsData)
	{
		goto DESTROY_SERVER;
	}
	
	server->m_sin = malloc(sizeof(struct sockaddr_in));
	if(!server->m_sin)
	{
		goto DESTROY_LIST;
	}

	server->m_serverSocket = MakeSocket();
	if(FAIL == server->m_serverSocket)
	{
		goto DESTROY_MSIN;
	}
	
	if(FAIL == InitTCPServer(server->m_sin, _data->m_port, server->m_serverSocket, _data->m_queueSize))
	{
		goto DESTROY_SOCKET;
	}
	
	return server;
	
DESTROY_SOCKET:
	close(server->m_serverSocket);
DESTROY_MSIN:
	free(server->m_sin);
DESTROY_LIST:
	ListDestroy(&server->m_clientsData, NULL);
DESTROY_SERVER:
	free(server);
	return NULL;
}

static int MakeSocket(void)
{
	int socketFD, optval= 1;
	socketFD = socket(PF_INET, SOCK_STREAM, 0);
    if(socketFD < 0) 
    {    
		perror("socket error");
		return -1;
    }
    
	if(FAIL == setsockopt(socketFD, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)))
	{
		perror("socket error");
		return -1;
	}
	
   	return ConvertToNonBlockedSocket(socketFD);
}

static int ConvertToNonBlockedSocket(int socketFD)
{    
    int flags;
    if(FAIL ==(flags == fcntl(socketFD, F_GETFL)))
    {
    	perror("socket error");
    	return -1;
    }
    
    if(FAIL == fcntl(socketFD,  F_SETFL, flags | O_NONBLOCK))
    {
    	perror("socket error");
    	return -1;
    }
    return socketFD;
}

static int InitTCPServer(struct sockaddr_in* _sockaddr, size_t _port, int _socketFD, size_t _queueSize)
{
	
	memset(_sockaddr, 0, sizeof(struct sockaddr_in));
 	_sockaddr->sin_family = AF_INET;
 	_sockaddr->sin_addr.s_addr = INADDR_ANY;
 	_sockaddr->sin_port =  htons(_port);
 	
 	if(0 > bind(_socketFD , (struct sockaddr *) _sockaddr, sizeof(struct sockaddr_in)))
 	{
		perror("bind error");
		return -1;
 	} 
 	
 	if (listen(_socketFD, _queueSize) < 0)
 	{
		perror("listen error");
		return -1;
	}
	return 0;
}

void DestroyServer(Server* _server)
{

	close(_server->m_serverSocket);
	free(_server->m_sin);
	ListDestroy(&_server->m_clientsData, DestroyClientData);
	free(_server);
}

static int DestroyClientData(void* _element, void*_context)
{
	ClientData* ptr = _element;
	close(ptr->m_socket);
	free(_element);
}

void ServerRoutin(Server* _server)
{
	while(1)
	{
		CheckNewClients(_server);
		CheckCurrentClients(_server);
	}
}

static int CheckError()
{			
	return (errno != EAGAIN && errno != EMFILE && errno != EWOULDBLOCK)? -1 : 0;
}

static void InsertNewClient(int _socket, List* _list)
{
	ClientData* newclient = malloc(sizeof(ClientData));
	if(newclient)
	{
		newclient->m_socket = ConvertToNonBlockedSocket(_socket);
		ListPushHead(_list, newclient);
	}
}

static int CheckNewClients(Server* _server)
{
	int sock, client_address_len;
	struct sockaddr_in client_add;
	client_address_len = sizeof(struct sockaddr_in);
	
	while(1)
	{
		sock = accept(_server->m_serverSocket, (struct sockaddr *)&client_add, &client_address_len);
		if(sock < 0)
		{
			return 0;
		}
		_server->m_callBackNewClient(_server->m_applicationContext, sock)?  InsertNewClient(sock, _server->m_clientsData): close(sock);
		
	}
}

static void HandleNewMessage(Server* _server, int _socket, void* _buf, ssize_t _count)
{
	_server->m_callBackNewMessage(_server->m_applicationContext,_buf, _count, _socket);
}

static void EraseClient(ListItr _itr)
{
    ClientData* ptr= ListItr_Remove(_itr);
    close(ptr->m_socket);
    free(ListItr_Remove(_itr));
}

static int CheckCurrentClients(Server* _server)
{
	ssize_t count;
	char buf[512];
	ListItr begin = ListItr_Begin(_server->m_clientsData);
    ListItr end =  ListItr_End(_server->m_clientsData);

	while(begin != end)
	{
		ClientData* ptr = ListItr_Get(begin);
		
		count = recv(ptr->m_socket, buf, sizeof(buf)-1, 0);
	 	if(count < 1)
	 	{
	 		if(errno != EAGAIN)
	 		{
	 			EraseClient(begin);
	 		}
/*			TODO deal with error */
	 	}
	 	else
	 	{
		 	HandleNewMessage(_server, ptr->m_socket, buf, count);
	 	
	 	}
	 	begin = ListItr_Next(begin);
	}
}

int SendMessage(char* _message, size_t _size, int _ID)
{
	int count;
	
	if(_message)
	{
		count = send(_ID, _message, _size, 0);
		if(count < 0)
	 	{
			perror("recvfrom error");
			return -1;
	 	}
	 	return 0; 
	}
	return -1;
}
