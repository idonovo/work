#include "server.h"


int main (int argc, char *argv[])
{
	int socketFD, clientSocket;
    struct sockaddr_in serv_addr, client_address;
	char* serverMessage = "server\n";
	socklen_t storageSize = sizeof(struct sockaddr_in);
	    
    socketFD = MakeSocket();
    
    InitTCPServer(&serv_addr, atoi(argv[1]), socketFD, atoi(argv[2]));
    
    clientSocket = WaitForNewClient(socketFD, &client_address);
    DataTransfer(clientSocket);
    CloseConnect(socketFD);
    CloseConnect(clientSocket);
	return 0;
}
