
#include <stdlib.h>
#include <string.h>

#include "ui.h"

#define PATH "/home/student/work/CDR/UI"	
#define KEY 'q'
#define TYPE 2


int main()
{
	ChannelData* data;
	char buffer[1024];
	int select;
	
	data = CreateTransmissionChannel(PATH, KEY, TYPE, NULL);
	if(!data)
	{
		printf("error");
	}
	
	while(1)
	{
		SendQuery(data);
	}	
	return 0;
}
