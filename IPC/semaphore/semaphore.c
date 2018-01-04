#include "semaphore.h"

#define QUEUE_FILENAME  "/home/student/work/IPC/semaphore"
#define QUEUE_BINARY_SEMAPHORE  "queueSem"
#define QUEUE_COUNTING_SEMAPHORE  "queueCountSem"
#define QUEUE_ID  'a'
#define FAIL -1
#define EMPTY 0
#define PRESENCE_CHANNEL 2
#define READER_CHANNEL 1
#define WRITERS_CHANNEL 3
#define PINGS 5


typedef struct MessageBox{
    long 	m_type;     
    char 	m_text[BUFFER_SIZE];   
}MessageBox;

/*************************************************************************/
/*TODO complete documantation*/
static int SetSemCounter(sem_t* _binSem, sem_t* _countSem, int _x);

static int IsCountSemEmpty(sem_t* _binSem, sem_t* _countSem);

sem_t* CreateSemaphore(char* _semName, int __value);

sem_t* OpenSemaphore(char* _semName);

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

	strcpy(_input->m_binSem, QUEUE_BINARY_SEMAPHORE);
	strcpy(_input->m_countSem, QUEUE_COUNTING_SEMAPHORE);
	_input->m_create =  1;
	_input->m_destroy =  1;
	_input->m_howToStop =  1;
	_input->m_nCycels =  2;
	_input->m_verb =  1;
	_input->m_speed =  10000;
	_input->m_pings = PINGS;
	strcpy(_input->m_file, QUEUE_FILENAME);
	
	while ((c = getopt (argc, argv, "p: t: c: d: n: e: v: s: f: m:")) != -1)
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
			_input->m_nCycels = atoi(optarg);
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
		case 'p':
			_input->m_pings = atoi(optarg);
			break;
		case 'm':
			strcpy(_input->m_binSem, optarg);
			break;
		case 't':
			strcpy(_input->m_countSem, optarg);
			break;
		case '?':
			fprintf (stderr, "\n invalid argument inserted \n");
			continue;
		}
	}
	fprintf (stderr,"Usage: %d [-v]  %d [-s]  %s [-f]  %d [-c] %d [-d]  %d [-e]  %d [-n] \n", _input->m_verb, _input->m_speed, _input->m_file, _input->m_create, _input->m_destroy, _input->m_howToStop, _input->m_nCycels);
	return ;
}
/******************************************************************************/
int BePong(Input* _input)
{
	sem_t* binarySem;
	sem_t* countingSem;
	int key, msqid, flag;
	MessageBox readMessageBox;
	MessageBox writeMessageBox;
	
	binarySem = OpenSemaphore(_input->m_binSem);
	if (SEM_FAILED == binarySem)
    {
         perror("sem_open");
         exit(EXIT_FAILURE);   
    }
	
	countingSem = OpenSemaphore(_input->m_countSem);
	if (SEM_FAILED == countingSem)
    {
         perror("sem_open");
         exit(EXIT_FAILURE);   
    }
	
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
	
	
	for(;;)
	{
	    
	    flag = IsCountSemEmpty(binarySem, countingSem);
	    if(FAIL == flag)  
	    {	    
	        exit(EXIT_FAILURE);
	    }
	    
	    if(EMPTY == flag)
	    {
	        break;
	    }
           	
       	if(FAIL == PongRoutine(msqid, &readMessageBox, &writeMessageBox, _input))
       	{
            exit(EXIT_FAILURE);
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
	sem_t* binarySem;
	sem_t* countingSem;
	int key, msqid;
	MessageBox readMessageBox;
	MessageBox writeMessageBox;
	
	binarySem = CreateSemaphore(_input->m_binSem, 1);
	if (SEM_FAILED == binarySem)
    {
         perror("sem_open");
         exit(EXIT_FAILURE);   
    }
    
    countingSem = CreateSemaphore(_input->m_countSem, _input->m_pings);
	if (SEM_FAILED == countingSem)
    {
         perror("sem_open");
         exit(EXIT_FAILURE);   
    }
    
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
	
	if(FAIL == SetSemCounter(binarySem, countingSem, 1)) 
    {
            exit(EXIT_FAILURE);
    } 
	
	for(i=0; i < _input->m_nCycels; ++i)
	{
		if(FAIL == PingRoutine(msqid, &readMessageBox, &writeMessageBox, _input)) 
       	{
            exit(EXIT_FAILURE);
        } 
    } 

 	if(FAIL == SetSemCounter(binarySem, countingSem, 0)) 
    {
            exit(EXIT_FAILURE);
    } 
      	
    exit(EXIT_SUCCESS);
    
}
 
/*********************************************************************/
static int SetSemCounter(sem_t* _binSem, sem_t* _countSem, int _x)
{
    
    int flag; 
    
    if (FAIL== sem_wait(_binSem))
    {
         perror("sem_wait failed");
         return -1; 
    }
    
    if(0 == _x)
    {    
        if(FAIL== sem_post(_countSem))
        {
            perror("sem_post failed");
            flag = FAIL;; 
        }
        flag =1;  
    }
    else
    {
        if(FAIL== sem_wait(_countSem))
        {
            perror("sem_post failed");
            flag = FAIL;; 
        }
        flag = 1;   
    }

    if(FAIL== sem_post(_binSem))
    {
         perror("sem_post failed");
         return -1; 
    }
    return flag;

}

static int IsCountSemEmpty(sem_t* _binSem, sem_t* _countSem)
{
    
    int value;
    
    if (FAIL== sem_wait(_binSem))
    {
         perror("sem_wait failed");
         return -1; 
    }
    
    if(FAIL == sem_getvalue(_countSem, &value));
    {
         perror("sem_get value failed");
         return -1; 
    }

    if(FAIL== sem_post(_binSem))
    {
         perror("sem_post failed");
         return -1; 
    }
    
    return value > 0 ? 1 : 0;
}

sem_t* CreateSemaphore(char* _semName, int _value)
{
    sem_t* sem = sem_open(_semName, O_CREAT, 0666, _value);

    return sem;
}

sem_t* OpenSemaphore(char* _semName)
{
    sem_t* sem = sem_open(_semName, 0);

    if (SEM_FAILED == sem)
    {
         perror("sem_init failed");
         exit(EXIT_FAILURE);   
    }
    return sem;
}


static int WriteToQueue(int _msqid, MessageBox* _writeMessageBox, long _channel)
{
	
	_writeMessageBox->m_type = _channel;
	InitBuffer(_writeMessageBox->m_text, _channel);

	return msgsnd(_msqid, _writeMessageBox, BUFFER_SIZE, 0);
}

static int ReadFromQueue(int _msqid, MessageBox* _readMessageBox, long _channel)
{
	
	return msgrcv(_msqid, _readMessageBox, sizeof(_readMessageBox->m_text), _channel, IPC_NOWAIT);
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
			printf("recivied \"%s\"\n", _readMessageBox->m_text);
       	}
       	sleep(1);
    return 0;
}       
