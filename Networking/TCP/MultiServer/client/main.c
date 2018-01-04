#include "client.h"

int main (int argc, char *argv[])
{
	int socketFD;
    struct sockaddr_in server_address, from;
	socklen_t storageSize = sizeof(struct sockaddr_in);
	char* message = "client\n";
	int port = atoi(argv[1]);
	char* ip = argv[2];
	 
    socketFD = MakeSocket();
    
    ConnectToServer(&server_address, ip , port , socketFD);
    
    DataTransferWithServer(100, socketFD, message);
    CloseConnectWithServer(socketFD);
	return 0;
}
