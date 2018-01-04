#include <sys/types.h> 
#include <stdlib.h>  
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
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

void SendMassage(struct sockaddr_in6* _cl_addr, char* _ip, int _port, int _socketFD)
{
 	char* message = "client\n";
 	memset((char *) _cl_addr, 0, sizeof(struct sockaddr_in6));
	_cl_addr->sin6_family = AF_INET6;
	inet_pton(AF_INET6, _ip, _cl_addr->sin6_addr.s6_addr);
	_cl_addr->sin6_port = htons(_port); 
	 	
	sendto(_socketFD, message, strlen(message)+1, 0, (struct sockaddr*)_cl_addr, sizeof(struct sockaddr_in6));
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

void Client(int _port, char* _ip)
{
	int socketFD;
   	struct sockaddr_in6 cl_addr, from;
	socklen_t storageSize = sizeof(struct sockaddr_in6);
	 
    socketFD = MakeSocket();
    
	for (int i = 0; i < 5; i += 1)
	{		
		SendMassage(&cl_addr, _ip, _port, socketFD);	 	
	 	GetAndPrintMessage(&from, socketFD, &storageSize);
	}	

 	close(socketFD);   
}

int main (int argc, char *argv[])
{
	Client(atoi(argv[1]), argv[2]);
	return 0;
}
