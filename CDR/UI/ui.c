
#include <stdlib.h>
#include <string.h>

#include "ui.h"

#define UI_PATH "/home/student/work/CDR/UI/report.txt"


int SendQuery(ChannelData* _channelData)
{
	Query query = {0};
	int select;
	
	if(!_channelData)
	{
		return -1;
	}
	
	while(1)
	{
	printf("please enter your choice: \n\n 1. subscriber query \n 2. operator query \n 3. subscribers report\n 4. operators report \n 5. total report \n");
		scanf("%d", &select);
		switch(select)
		{
			case 1:
				printf("please enter MSISDN:\n");
				scanf("%s", query.m_subscriberMSISDN); 
				query.m_enum = 1;
				PushToChannel((void*)&query, sizeof(Query), _channelData);
				break;
			case 2:
				printf("please enter TUPLE:\n");
				scanf("%d", &query.m_operatorTuple); 
				query.m_enum = 2;
				PushToChannel((void*)&query, sizeof(Query), _channelData);
				break;
			case 3:
				printf("please check report.txt:\n");
				query.m_enum = 3;
				strcpy(query.m_path, UI_PATH);	
				PushToChannel((void*)&query, sizeof(Query), _channelData);
				break;
			case 4:
				printf("please check report.txt:\n");
				query.m_enum = 4;
				strcpy(query.m_path, UI_PATH);	
				PushToChannel((void*)&query, sizeof(Query), _channelData);
				break;
			case 5:
				printf("please check report.txt:\n");
				query.m_enum = 5;
				strcpy(query.m_path, UI_PATH);	
				PushToChannel((void*)&query, sizeof(Query), _channelData);
				break;
			case 6:
				query.m_enum = 6;
				PushToChannel((void*)&query, sizeof(Query), _channelData);
				return 0;	
		}
	}
	return 0;		
}
