#include <sys/types.h> 
#include <stdlib.h>  
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

unsigned int MakeSocket(void);
int ConnectToServer(struct sockaddr_in* server_address, char* _ip,  unsigned int _port, int _socketFD);
void DataTransferWithServer(unsigned int _numOfTransfers, unsigned int _socketFD, char* _massage);
void CloseConnectWithServer(unsigned int _socketFD);
