
#include "server.h"



unsigned int MakeSocket(void)
{
	unsigned int socketFD;
	socketFD = socket(PF_INET, SOCK_STREAM, 0);
    if (socketFD < 0) 
    {    
		perror("socket error");
    }
    
    return socketFD;
}

void InitTCPServer(struct sockaddr_in* _sockaddr,  unsigned int _port, unsigned int _socketFD, unsigned int _queueSize)
{
	
	memset(_sockaddr, 0, sizeof(struct sockaddr_in));
 	_sockaddr->sin_family = AF_INET;
 	_sockaddr->sin_addr.s_addr = INADDR_ANY;
 	_sockaddr->sin_port =  htons(_port);
 	
 	if(0 > bind(_socketFD , (struct sockaddr *) _sockaddr, sizeof(struct sockaddr_in)))
 	{
		perror("bind error");
 	} 
 	
 	if (listen(_socketFD, _queueSize) < 0)
 	{
		perror("listen error");
	}
}

int WaitForNewClient(unsigned int _socketFD, struct sockaddr_in* _client_address)
{
	int sock;
	int client_address_len = sizeof(struct sockaddr_in);
	
	sock = accept(_socketFD, (struct sockaddr *)_client_address, &client_address_len);
	
	if(sock < 1)
	{
		perror("accept error");
	}
	return sock;
}

void DataTransfer(unsigned int _socketFD)
{
	ssize_t count;
	char buf[512];
	char* serverMessage = "got message";
	while(1)
	{
		count = recv(_socketFD, buf, sizeof(buf)-1, 0);
	
	 	if(count < 0)
	 	{
			perror("recv error");
	 	}
	 	
	 	buf[count] = '\0';	
	 	printf("%s", buf); 
	 	
	 	if(strcmp(buf, "Exit") == 0)
	 	{
	 		return;
	 	}
	 	
	 	count = send(_socketFD, serverMessage, strlen(serverMessage)+1, 0);
	 	if(count < 0)
	 	{
			perror("send error");
	 	}
	}		
}

void CloseConnect(unsigned int _socketFD)
{
		close(_socketFD);
}



