#include "multi.h"


#define QUEUE_FILENAME  "/home/ido/Desktop/work/IPC/multiWriters"
#define QUEUE_ID  'a'
#define FAIL -1
#define PRESENCE_CHANNEL 2
#define READER_CHANNEL 1
#define WRITERS_CHANNEL 3



typedef struct MessageBox{
    long 	m_type;     
    char 	m_text[BUFFER_SIZE];   
}MessageBox;

/*************************************************************************/
/*TODO complete documantation*/
static int CheckChannelNotEmpty(int _msqid, MessageBox* _readMessageBox, long _channel);

static int WriteToQueue(int _msqid, MessageBox* _writeMessageBox, long _channel);

static int ReadFromQueue(int _msqid, MessageBox* _readMessageBox, long _channel);

static int BlockReadFromQueue(int _msqid, MessageBox* _readMessageBox, long _channel);

static int CreateQueue(int _key, int _flag);

static void InitBuffer(char* _buffer, long _channel);

static int PongRoutine(int _msqid, MessageBox* _readMessageBox, MessageBox* _writeMessageBox, Input* _input);

static int PingRoutine(int _msqid, MessageBox* _readMessageBox, MessageBox* _writeMessageBox, Input* _input);
/******************************************************************************/

void ParseInput(Input* _input, int argc, char **argv)
{
	
	int c;

	_input->m_create =  1;
	_input->m_destroy =  1;
	_input->m_howToStop =  1;
	_input->m_nCycels =  10;
	_input->m_verb =  1;
	_input->m_speed =  10000;
	strcpy(_input->m_file, QUEUE_FILENAME);
	
	while ((c = getopt (argc, argv, "c: d: n: e: v: s: f")) != -1)
	{
		switch (c)
		{
		case 'c':
			_input->m_create = atoi(optarg);
			break;
		case 'd':
			_input->m_destroy = atoi(optarg);
			break;
		case 'n':
			_input->m_howToStop = atoi(optarg);
			break;
		case 'e':
			_input->m_nCycels = (size_t)atoi(optarg);
			break;
		case 'v':
			_input->m_verb = atoi(optarg);
			break;
		case 's':
			_input->m_speed = atoi(optarg);
			break;
		case 'f':
			strcpy(_input->m_file, optarg);
			break;
		case '?':
			fprintf (stderr, "\n invalid argument inserted \n");
			continue;
		}
	}
	fprintf (stderr,"Usage: %d [-v]  %u [-s]  %s [-f]  %d [-c] %d [-d]  %d [-e]  %d [-n] \n", _input->m_verb, _input->m_speed, _input->m_file, _input->m_create, _input->m_destroy, _input->m_howToStop, _input->m_nCycels);
	return ;
}
/******************************************************************************/
int BePong(Input* _input)
{
	
	int key, msqid;
	MessageBox readMessageBox;
	MessageBox writeMessageBox;
	
	key = ftok(_input->m_file, QUEUE_ID);
	
	if(FAIL == key)
	{
		perror("ftok");
	    exit(EXIT_FAILURE);
	}
	
	msqid = msgget(key, 0);
	
	if(FAIL == msqid)
	{
		perror("msgget");
	    exit(EXIT_FAILURE);
	}
	printf("my qid: %d\n", msqid);
	printf("Lets start reading:");
	
	while(CheckChannelNotEmpty(msqid, &readMessageBox, PRESENCE_CHANNEL))
	{    
           	
        while(CheckChannelNotEmpty(msqid, &readMessageBox, READER_CHANNEL))
        {
           	
           	if(FAIL == PongRoutine(msqid, &readMessageBox, &writeMessageBox, _input))
           	{
                exit(EXIT_FAILURE);
            }
        }
     }
    
	if(_input->m_destroy)
    {
    	msgctl(msqid, IPC_RMID, NULL);
    } 
      	
    exit(EXIT_SUCCESS);
}

/******************************************************************************/
int BePing(Input* _input)
{
	
	size_t i;
	int key, msqid;
	MessageBox readMessageBox;
	MessageBox writeMessageBox;
	
	key = ftok(_input->m_file, QUEUE_ID);
	
	if(FAIL == key)
	{
		perror("ftok");
	    exit(EXIT_FAILURE);
	}
	
	msqid = CreateQueue(key, _input->m_create);
	if(FAIL == msqid)
	{
		perror("msgget");
	    exit(EXIT_FAILURE);
	}
	printf("my qid: %d\n", msqid);
	
	printf("Lets start writing:");
	
	if(FAIL == WriteToQueue(msqid, &writeMessageBox, PRESENCE_CHANNEL)) 
    {
            perror("msgsnd");
            exit(EXIT_FAILURE);
    } 
	
	for(i=0; i < _input->m_nCycels; ++i)
	{
		if(FAIL == PingRoutine(msqid, &readMessageBox, &writeMessageBox, _input)) 
       	{
            exit(EXIT_FAILURE);
        } 
    } 

    if(FAIL == ReadFromQueue(msqid, &readMessageBox, PRESENCE_CHANNEL)) 
    {
       perror("msgrcv");
       exit(EXIT_FAILURE);
    }
      	
    exit(EXIT_SUCCESS);
    
}
 
/*********************************************************************/
static int CheckChannelNotEmpty(int _msqid, MessageBox* _readMessageBox, long _channel)
{
	if(msgrcv(_msqid, _readMessageBox, sizeof(_readMessageBox->m_text), _channel, IPC_NOWAIT) == -1)
	{
		return 0;
	}
	
	msgsnd(_msqid, _readMessageBox, BUFFER_SIZE, 0);
	
	return 1;
}
static int WriteToQueue(int _msqid, MessageBox* _writeMessageBox, long _channel)
{
	
	_writeMessageBox->m_type = _channel;
	InitBuffer(_writeMessageBox->m_text, _channel);

	return msgsnd(_msqid, _writeMessageBox, BUFFER_SIZE, 0);
}

static int ReadFromQueue(int _msqid, MessageBox* _readMessageBox, long _channel)
{
	int flag = msgrcv(_msqid, _readMessageBox, sizeof(_readMessageBox->m_text), _channel, IPC_NOWAIT);

	return flag;
}

static int BlockReadFromQueue(int _msqid, MessageBox* _readMessageBox, long _channel)
{
	return msgrcv(_msqid, _readMessageBox, sizeof(_readMessageBox->m_text), _channel, 0);

}


static int CreateQueue(int _key, int _flag)
{
	return _flag? msgget(_key, 0666 | IPC_CREAT): msgget(_key, 0666 | IPC_EXCL);
}

static void InitBuffer(char* _buffer, long _channel)
{

	if(3 == _channel)
	{
		strcpy(_buffer, "ping");
	}
	if(1 == _channel)
	{
		strcpy(_buffer, "pong");
	}  
	if(2 == _channel)
	{
		strcpy(_buffer, "new Writer");
	}    

}

static int PongRoutine(int _msqid, MessageBox* _readMessageBox, MessageBox* _writeMessageBox, Input* _input)
{           
        if(FAIL == ReadFromQueue(_msqid, _readMessageBox, READER_CHANNEL)) 
       	{
            perror("msgrcv");
            return FAIL;
        }
        
        if(_input->m_verb)
       	{
		    printf("recived - \"%s\"\n", _readMessageBox->m_text);
       	}
        
        if(_input->m_speed)
       	{
   	    	sleep(1);
   	    	usleep(_input->m_speed);   	
       	}
        
        if(FAIL == WriteToQueue(_msqid, _writeMessageBox, WRITERS_CHANNEL)) 
       	{
            perror("msgsnd");
            return FAIL;
        }
        
        sleep(1); 
    return 0;
}        
 
static int PingRoutine(int msqid, MessageBox* _readMessageBox, MessageBox* _writeMessageBox, Input* _input)        
{
        
        if(FAIL == WriteToQueue(msqid, _writeMessageBox, READER_CHANNEL)) 
       	{
            perror("msgsnd");
            return FAIL;
        } 
		
		if(_input->m_speed)
       	{
   	    	usleep(_input->m_speed);    	
       	}
		sleep(1);
		if(FAIL == BlockReadFromQueue(msqid, _readMessageBox, WRITERS_CHANNEL)) 
       	{
            perror("msgrcv");
            return FAIL;
        }
        
        if(_input->m_verb)
       	{
			printf("recived \"%s\"\n", _readMessageBox->m_text);
       	}
       	sleep(1);
    return 0;
}       
