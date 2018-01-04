#include <sys/types.h> 
#include <stdlib.h>  
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

unsigned int MakeSocket(void)
{
	unsigned int socketFD;
	socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0) 
    {    
		perror("socket error");
    }
    
    return socketFD;
}

int ConnectToServer(struct sockaddr_in* server_address, char* _ip,  unsigned int _port, int _socketFD)
{
	memset(server_address, 0, sizeof(struct sockaddr_in));
 	server_address->sin_family = AF_INET;
 	server_address->sin_addr.s_addr = inet_addr(_ip);
 	server_address->sin_port = htons(_port); 
 	if(0 > connect(_socketFD, (struct sockaddr*)server_address, sizeof(struct sockaddr_in)))
	{    
		perror("connect error");
		return -1;
    }
    
    return 0;
}	

void DataTransferWithServer(unsigned int _numOfTransfers, unsigned int _socketFD, char* _massage)
{
	ssize_t count, i;
	char buf[512];
	char* serverMessage = "got message";
	
	for (i = 0; i < _numOfTransfers; i += 1)
	{
	 	count = send(_socketFD, _massage, strlen(_massage)+1, 0);
	 	if(count < 0)
	 	{
			perror("recvfrom error");
	 	}
	 		 	
		count = recv(_socketFD, buf, sizeof(buf)-1, 0);
		printf("%d\n", count);
	 	if(count < 0)
	 	{
			perror("recv error");
	 	}
	 	
	 	buf[count] = '\0';	
	 	printf("%s\n", buf); 
	}	
}

void CloseConnectWithServer(unsigned int _socketFD)
{
	ssize_t count;
	char* exitMessage = "Exit";
	count = send(_socketFD, exitMessage, strlen( exitMessage)+1, 0);
 	if(count < 0)
 	{
		perror("recvfrom error");
 	}
 	close(_socketFD);
}


