
#include <sys/types.h> 
#include <stdlib.h>  
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

unsigned int MakeSocket(void);

void InitTCPServer(struct sockaddr_in* _sockaddr,  unsigned int _port, unsigned int _socketFD, unsigned int _queueSize);

int WaitForNewClient(unsigned int _socketFD, struct sockaddr_in* client_address);

void DataTransfer(unsigned int _socketFD);

void CloseConnect(unsigned int _socketFD);


