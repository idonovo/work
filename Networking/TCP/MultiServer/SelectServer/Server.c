#include "Server.h"
#include <stdlib.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <arpa/inet.h>

#define FAIL -1
#define TRUE 1
#define FALSE 0
#define MAX_FD 1024
#define	SAFETY_RANGE 0

typedef struct ClientData 
{
    int m_socket;
}ClientData;

struct Server 
{
    List* m_clientsData;
    int m_serverSocket;
    struct sockaddr_in* m_sin;
    fd_set m_fdReader;
   	CallBackNewMessage m_callBackNewMessage;
    CallBackNewClient m_callBackNewClient;
    void* m_applicationContext;
   	unsigned int m_queueSize;
   	unsigned int m_numOfclients;
   	int m_isRunning;
   	 
};
/******************************************************************************************************/
static int DestroyClientData(void*, void*);
static int MakeSocket(void);
static int InitTCPServer(struct sockaddr_in* _sockaddr, size_t _port, int _socketFD, size_t _queueSize);
static void AddServerSocketToSet(fd_set* _set, int _socket);
static void AddNewClient(Server* _server);
static void InsertNewClient(int _socket, List* _list, fd_set* _set);
static void SearchForClientMessage(Server* _server, fd_set* _set);
static void HandleNewMessage(Server* _server,  ListItr _itr);
static void EraseClient(Server* _server, ListItr _itr);
static void RejectClient(Server*_server, int sock);
static int RemoveBySocket(Server* _server, int _ID);
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
	server->m_queueSize = _data->m_queueSize;
	server->m_numOfclients = 0;
	server->m_isRunning = TRUE;
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
	
	if(FAIL == InitTCPServer(server->m_sin, _data->m_port, server->m_serverSocket, server->m_queueSize))
	{
		goto DESTROY_SOCKET;
	}
	
	AddServerSocketToSet(&server->m_fdReader, server->m_serverSocket);
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

static void AddServerSocketToSet(fd_set* _set, int _socket)
{
    FD_ZERO(_set);
    FD_SET(_socket, _set);
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

void ServerRoutine(Server* _server)
{
	int activity;
	while(1)
	{
		fd_set tempSet;
		FD_ZERO(&tempSet);
		tempSet = _server-> m_fdReader;
		
		if(!_server->m_isRunning)
		{
			return;
		}
		
		activity = select(MAX_FD , &tempSet, NULL , NULL , NULL);
		
		if ((activity < 0) && (errno!=EINTR)) 
		{
		    perror("select error");
		}
		else if((FD_ISSET(_server->m_serverSocket, &tempSet)))
		{
			AddNewClient(_server);
		}
		else
		{
			SearchForClientMessage(_server,  &tempSet);
		}
	}
}

static void AddNewClient(Server* _server)
{
    int sock, client_address_len;
    char* IP;
	struct sockaddr_in client_add;
	client_address_len = sizeof(struct sockaddr_in);

	sock = accept(_server->m_serverSocket, (struct sockaddr *)&client_add, &client_address_len);
	if(sock < 0)
	{
		return;
	}
	 
    if(_server->m_numOfclients == (_server->m_queueSize - SAFETY_RANGE))
    {
    	RejectClient(_server, sock);
    	return;
    }
    
    ++_server->m_numOfclients;
	printf("num of clients: %d sock %d",_server->m_numOfclients, sock);
	
	_server->m_callBackNewClient(_server->m_applicationContext, inet_ntoa(client_add.sin_addr), sock)? 
	InsertNewClient(sock, _server->m_clientsData, &_server-> m_fdReader): close(sock);
    
}

static void RejectClient(Server*_server, int sock)
{
	close( sock);
	FD_CLR(sock, &_server-> m_fdReader);

}

static void InsertNewClient(int _socket, List* _list, fd_set* _set)
{
	ClientData* newclient = malloc(sizeof(ClientData));
	if(newclient)
	{
		newclient->m_socket = _socket;
		ListPushHead(_list, newclient);
	}
	FD_SET(_socket, _set);
}

static void SearchForClientMessage(Server* _server, fd_set* _set)
{

	ListItr begin = ListItr_Begin(_server->m_clientsData);
    ListItr end =  ListItr_End(_server->m_clientsData);

	while(begin != end)
	{
		ClientData* ptr = ListItr_Get(begin);
		if(FD_ISSET(ptr->m_socket, _set))
		{
		    HandleNewMessage(_server, begin);
		    return;
		} 
	 	begin = ListItr_Next(begin);
	 }
}

static void HandleNewMessage(Server* _server,  ListItr _itr)
{
    ssize_t count;
	char buf[512];
	
	ClientData* ptr = ListItr_Get(_itr);
	count = recv(ptr->m_socket, buf, sizeof(buf)-1, 0);
 	if(count < 1)
 	{	
 		if(errno != EAGAIN)
 		{
 			EraseClient(_server, _itr);
 		}
 	}
 	else if(count == 0)
 	{ 		
 		EraseClient(_server, _itr);
 	}
 	else
 	{
	 	_server->m_callBackNewMessage(_server->m_applicationContext, buf, count, ptr->m_socket);
 	}
}

static void EraseClient(Server* _server, ListItr _itr)
{
    ClientData* ptr= ListItr_Remove(_itr);
    close(ptr->m_socket);
    FD_CLR(ptr->m_socket, &_server-> m_fdReader);
    free(ptr);
    --_server->m_numOfclients;
}

static int RemoveBySocket(Server* _server, int _ID)
{
	ListItr begin = ListItr_Begin(_server->m_clientsData);
    ListItr end =  ListItr_End(_server->m_clientsData);

	while(begin != end)
	{
		ClientData* ptr = ListItr_Get(begin);
		if(ptr->m_socket == _ID)
		{
		    EraseClient(_server,  begin);
		    return 0;
		} 
	 	begin = ListItr_Next(begin);
	}
	return -1;
}


void StopServer(Server* _server)
{
	_server->m_isRunning = FALSE;
}

int SendMessage(Server* _server,  void* _message, size_t _size, int _ID)
{
	int count;
	
	if(_message)
	{
		count = send(_ID, _message, _size, MSG_NOSIGNAL);
		if(count < 0)
	 	{	
			perror("recvfrom error");
			RemoveBySocket(_server, _ID);
			return -1;
	 	}
	 	else if(count== 0)
	 	{
	 		RemoveBySocket(_server, _ID);
	 		return -1;
	 	}
	 	return 0; 
	}
	return -1;
}

int DisconnectClient(Server* _server, int _ID)
{
    return RemoveBySocket(_server, _ID);
}


