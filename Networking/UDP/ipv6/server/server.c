#include <sys/types.h> 
#include <stdlib.h>  
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int MakeSocket(void)
{
	int socketFD;
	socketFD = socket(AF_INET6, SOCK_DGRAM, 0);
    if (socketFD < 0) 
    {    
		perror("socket error");
    }
    return socketFD;

}

void BindSocket(struct sockaddr_in6* _serv_addr, int _port, int _socketFD)
{
	memset(_serv_addr, 0, sizeof(struct sockaddr_in6));
 	_serv_addr->sin6_family = AF_INET6;
 	_serv_addr->sin6_addr = in6addr_any;
 	_serv_addr->sin6_port =  htons(_port);
 	
 	if(0 > bind(_socketFD , (struct sockaddr *) _serv_addr, sizeof(struct sockaddr_in6)))
 	{
		perror("bind error");
 	}
}

void GetAndPrintMessage(struct sockaddr_in6* _sockaddr, int _socketFD, socklen_t* _storageSize)
{
	ssize_t count;
	char buf[512];
	
	count = recvfrom(_socketFD, buf, sizeof(buf)-1, 0, (struct sockaddr*) _sockaddr, _storageSize);
	
 	if(count < 0)
 	{
		perror("recvfrom error");
 	}
 	
 	buf[count] = '\0';
 	
 	printf("%s\n", buf); 	
}


void Server(int _port)
{
	int socketFD;
    struct sockaddr_in6 serv_addr, from;
	ssize_t count;
	char* serverMessage = "server\n";
	socklen_t storageSize = sizeof(struct sockaddr_in6);
	    
    socketFD = MakeSocket();
    
    BindSocket(&serv_addr,_port, socketFD);
 	 
    for (int i = 0; i < 5; i += 1)
    {
	 	GetAndPrintMessage(&from, socketFD, &storageSize);
	 	sendto(socketFD, serverMessage, strlen(serverMessage)+1, 0, (struct sockaddr*)&from, sizeof(from));
	 	sleep(2);
    }
 	 
 	close(socketFD);
}

int main (int argc, char *argv[])
{
	Server(atoi(argv[1]));
	return 0;
}
