#include "smartClient.h"
#include <sys/types.h> 
#include <stdlib.h>  
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>


int main (int argc, char *argv[])
{
	int i, port = atoi(argv[1]);
	char* ip = argv[2];
	char* message = "i am a message";

	SmartClient* smart = CreateSmartClient(2, port, ip);
	SmartClientRoutine(smart, 20);
	DestroySmartClient(smart);
	return 0;
}
