
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#include "TransmissionData.h"
#include "../../inc/logger.h"
#include "../../inc/config.h"

#define	FAIL -1
#define	QUEUE_CHANNEL 1
#define QUEUE_FILENAME  "/home/student/work/CDR/FEEDER"
#define QUEUE_ID 'f'
#define BUFFER_SIZE 256
#define LAST_MESSAGE "finish!!"
#define LOG_WRITE(x, i)  LogWrite((x), (i), __func__, __LINE__, __FILE__, NULL);


struct ChannelData
{
	int 		m_channelID;
	long 		m_type;
	LogData* 	m_logData;
};

typedef struct MessageBox MessageBox;

struct MessageBox
{
 	long m_type;     
    char m_buffer[BUFFER_SIZE];  
};
/***********************************************************************************/
static void GetConfigChannel(ChannelData* _channelData, char* _configFileName);
static void SetDefaultChannel(ChannelData* _channelData);
static void SetParseValue(FILE* _fp, ChannelData* _channelData);
static int IsLastMessage(char* _context);
static int InitChannel(ChannelData* _channelData, char* _feederPath, char _feederKey, int _type);
/***********************************************************************************/

/* TODO transfer to config module
static void GetConfigChannel(ChannelData* _channelData, char* _configFileName)
{
	FILE* fp;
	
	SetDefaultChannel(_channelData);
	
	if(!_configFileName)
	{
		return;
	}
	
	fp = fopen(_configFileName, "r");
	
	if(fp)
	{	
		SetParseValue(fp, _channelData); 
	}
	
	fclose(fp);
	
	return;	
}

static void SetDefaultChannel(ChannelData* _channelData)
{
	strcpy(_channelData->m_path, QUEUE_FILENAME);
	_channelData->m_key = QUEUE_ID;
	_channelData->m_type = QUEUE_CHANNEL;
	return; 
}

static void SetParseValue(FILE* _fp, ChannelData* _channelData)
{
	char buffer1[BUFFER_SIZE];
	char buffer2[BUFFER_SIZE];
	char buffer3[BUFFER_SIZE];
	 
	while (!feof(_fp))
	{
		
		fgets(buffer1, BUFFER_SIZE, _fp);
		sscanf(buffer1,"[%[^]\n]",buffer2);
		if(strcmp(buffer2, "#CHANNEL") == 0)
		{	
			while(!feof(_fp))
			{	
				sscanf(buffer1," \n%[^ =] = %[^\n]", buffer2, buffer3);
				if(strcmp(buffer2, "PATH") == 0)
				{
					strcpy(_channelData->m_path, buffer3);
				}
			
				if(strcmp(buffer2, "KEY") == 0)
				{
					_channelData->m_key = buffer3[0];
				}
				
				if(strcmp(buffer2, "TYPE") == 0)
				{
					_channelData->m_type = buffer3[0];
				}
				fgets(buffer1, BUFFER_SIZE, _fp);
			}
		}
	}
	return;
}
*/

static int InitChannel(ChannelData* _channelData, char* _feederPath, char _feederKey, int _type)
{	
	int key;
	key = ftok(_feederPath, _feederKey);
	
	if(FAIL == key)
	{
		return -1;
	}
	_channelData->m_channelID = msgget(key, 0666 | IPC_CREAT);
	if(FAIL == _channelData->m_channelID)
	{
		return -1;
	}
	_channelData->m_type = _type;
	
	return 0;
}
/*********************************************************************/
ChannelData* CreateTransmissionChannel(char* _feederPath, char _feederkey, int _type, LogData* _log)
{
	ChannelData* channelData;
	
	channelData = malloc(sizeof(ChannelData));
	if(!channelData)
	{
		return NULL;
	}
	channelData->m_logData = _log;
	/*LOG_WRITE(channelData->m_logData, 1); */
	
	if(FAIL == InitChannel(channelData, _feederPath, _feederkey, _type))
	{
		return NULL;
	}
	
	/*LOG_WRITE(channelData->m_logData, 1); */
	return channelData;
}

int PushToChannel(void* _context, size_t _size, ChannelData* _data)
{
	MessageBox messageBox;
	
	if(!_context || !_data)
	{
		return -1;
	}
	/*LOG_WRITE(channelData->m_logData, 1); */
	
	messageBox.m_type = _data->m_type;
	memcpy(messageBox.m_buffer, _context, _size);
	
	if(FAIL == msgsnd(_data->m_channelID, &messageBox, BUFFER_SIZE, 0))
	{
	    /*LOG_WRITE(channelData->m_logData, 5); */
	    return -1;
	}
	return 0;
}

int SendLastMessage(ChannelData* _data)
{
	MessageBox messageBox;
	
	if(!_data)
	{
		return -1;
	}

	/*LOG_WRITE(_data->m_logData, 1); */
	messageBox.m_type = _data->m_type;
	memcpy(messageBox.m_buffer, LAST_MESSAGE, sizeof(LAST_MESSAGE));
	
	if(FAIL == msgsnd(_data->m_channelID, &messageBox, BUFFER_SIZE, 0))
	{
	    /*LOG_WRITE(_data->m_logData, 5); */
	    return -1;
	}
	return 0;
}

int ReadFromChannel(void* _context, size_t _size, ChannelData* _data)
{
	MessageBox messageBox;
	
	if(!_context || !_data)
	{
		return -1;
	}
	
	/*LOG_WRITE(_data->m_logData, 1); */
	
	
	if(FAIL == msgrcv(_data->m_channelID, &messageBox, BUFFER_SIZE, _data->m_type, IPC_NOWAIT))
	{
		/*LOG_WRITE(_data->m_logData, 5); */
		return -1;
	}
	
	memcpy((char*)_context, messageBox.m_buffer, _size);
	/*LOG_WRITE(_data->m_logData, 1); */
	
	return IsLastMessage((char*)_context);
}

int ReadLastMessage(ChannelData* _data)
{
	MessageBox messageBox;
	void* context;
	
	if(!_data)
	{
		return -1;
	}
	
	/*LOG_WRITE(_data->m_logData, 1); */
	if(FAIL == msgrcv(_data->m_channelID, &messageBox, BUFFER_SIZE, _data->m_type, IPC_NOWAIT))
	{
		/*LOG_WRITE(_data->m_logData, 5); */
		return -1;
	}
	
	return IsLastMessage(messageBox.m_buffer);
}

static int IsLastMessage(char* _context)
{
	return strcmp(_context, LAST_MESSAGE) == 0 ? 1 : 0;
}

void DestroyChannel(ChannelData* _data)
{
	if(!_data)
	{
		return;
	}
	/*LOG_WRITE(channelData->m_logData, 1); */
	
	msgctl(_data->m_channelID, IPC_RMID, NULL);
	free(_data);
	return;
}

