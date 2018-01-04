#include "client.h"

int main (int argc, char *argv[])
{
	int socketFD;
    struct sockaddr_in server_address, from;
	socklen_t storageSize = sizeof(struct sockaddr_in);
	char* message = "client\n";
	 
    socketFD = MakeSocket();
    
    ConnectToServer(&server_address, argv[2], atoi(argv[1]), socketFD);
    
    DataTransferWithServer(100, socketFD, message);
    CloseConnectWithServer(socketFD);
	return 0;
}
