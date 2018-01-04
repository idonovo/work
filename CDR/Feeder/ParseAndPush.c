#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include "protocol.h"
#include "ParseAndPush.h"
#include "fidders.h"

#define EVENT_SIZE  (sizeof(struct inotify_event))
#define BUF_LEN     ((EVENT_SIZE + 16))
#define SIZE 256
#define TUPLE 23456
#define CDR_LINE 256
#define PATH "/home/student/work/CDR/CDR_FILES/"

struct FeedersContext
{
	/*Queue*				m_cdrFilesQueue; */
	ChannelData* 		m_channel;
	/*size_t 				m_numOfFeeders; */
	/*int 				m_shutDownFlag; */
	char 				m_recPath[64];
	char 				m_workPath[64];
	char 				m_donePath[64];
	char                m_curCdrFile[32];		
};


int Parse(char* _buffer, CdrData* _cdr)
{
    char type[6];
    char tuple[6];
    char parTuple[6];
    char duration[6];
    char upload[6];
    char download[6];
    
    if(!_buffer)
    {
        return -1;
    }
	
	sscanf(_buffer,"%[^ |] | %[^ |] | %[^ |] | %[^ |] | %[^ |] | %[^ |] | %[^ |] | %[^ |] | %[^ |] | %[^ |] | %[^ |] | %[^ |] | %[^ |] | %[^ \n]", _cdr->m_imsi, _cdr->m_msidn, _cdr->m_imei, _cdr->m_opratorBrandName, tuple, type, _cdr->m_date, _cdr->m_time, duration, download, upload, _cdr->m_ParMSIDN, parTuple);
	
	_cdr->m_tuple = atoi(tuple);
   	_cdr->m_duration = atoi(duration);
   	_cdr->m_downloaded = atoi(download);
    _cdr->m_uploaded = atoi(upload);
    _cdr->m_ParOpratorTuple = atoi(parTuple); 
    
    if(strcmp(type, "MOC") == 0)
    {
        _cdr->m_type = 'a'; 
    }
    else if(strcmp(type, "MTC") == 0)
    {
        _cdr->m_type = 'b'; 
    }
    else if(strcmp(type, "SMS_MO") == 0)
    {
        _cdr->m_type = 'c'; 
    }
    else if(strcmp(type, "SMS_MT") == 0)
    {
        _cdr->m_type = 'd'; 
    }
    else if(strcmp(type, "GPRS") == 0)
    {
        _cdr->m_type = 'e'; 
    } 
    
    if(_cdr->m_ParOpratorTuple == TUPLE)
    {
        _cdr->m_ParOprator = 'a';
    } 
    _cdr->m_ParOprator = 'b';
    return 0;
}



void* ReadCdrFile(void* _context)
{
    
    FILE* fp;
    CdrData data;
    char buffer[256];
    
    fp = fopen(((FeedersContext*)_context)->m_curCdrFile, "r");
    if(!fp)
    {
        pthread_exit(NULL);
    }
    
    fgets(buffer, CDR_LINE, fp);
    memset(&data, 0, sizeof(CdrData));
    
    while(fgets(buffer, CDR_LINE, fp))
    {
        Parse(buffer, &data);
        PushToChannel(&data, sizeof(CdrData), ((FeedersContext*)_context)->m_channel);
        memset(&data, 0, sizeof(CdrData));
    }
    SendLastMessage(((FeedersContext*)_context)->m_channel); 
   	pthread_exit(NULL);
}


int NotifyCdrFile(FeedersContext* _context)
{

	int length, fd, wd, i = 0;
	char buffer[BUF_LEN];
	struct inotify_event *event;
	
	fd = inotify_init();

	if( fd < 0 )
	{
		return -1;
	}

	wd = inotify_add_watch( fd, _context->m_recPath, IN_MOVED_TO | IN_CREATE );
	length = read( fd, buffer, BUF_LEN );

	if ( length < 0 )
	{
		return -1;
	}

	while ( i < length )
	{
		event= ( struct inotify_event * ) &buffer[ i ];
		if(event->len)
		{
			strcat(_context->m_curCdrFile, event->name);
		}
		i += EVENT_SIZE + event->len;
	}

	inotify_rm_watch( fd, wd);
	close(fd);
	return 0;
}
 
