#include "mqueues.h"

/*************************************************************************/

void ParseInput(Input* _input, int argc, char **argv)
{
	
	int c;

	_input->m_create =  1;
	_input->m_destroy =  1;
	_input->m_howToStop =  1;
	_input->m_nCycels =  6;
	_input->m_verb =  1;
	_input->m_speed =  1;
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
		case '?':
			fprintf (stderr, "\n invalid argument inserted \n");
			continue;
		}
	}
	fprintf (stderr,"Usage: %d [-v]  %u [-s]  %s [-f]  %d [-c] %d [-d]  %d [-e]  %d [-n] \n", _input->m_verb, _input->m_speed, _input->m_file, _input->m_create, _input->m_destroy, _input->m_howToStop, _input->m_nCycels);
	return ;
}

void InsertToBuffer(char* _readbuffer, char _x, int _size)
{
	size_t i;
	
	for(i = 0; i < _size; ++i)
	{
		_readbuffer[i] = _x;
	}
	return;
}

int CreateQueue(int _key, int _flag)
{
	return _flag? msgget(_key, 0666 | IPC_CREAT): msgget(_key, 0666 | IPC_EXCL);
}
	
void InitMessageBox(MessageBox* _messageBox, char* _buffer, int _pid)
{	
	_messageBox->m_type = 1;
	strcpy(_messageBox->m_text, _buffer);
	_messageBox->m_pid =  _pid;
}  

int IsLastMessage(MessageBox* _messageBox)
{
	
	if(strcmp(_messageBox->m_text, MSG_STOP) == SUCCESS)
	{
		return 1;
	}
	
	if(_messageBox->m_type == -1)
	{
		return 1;
	}
	
	return 0;
}

int SendEOF(MessageBox* _messageBox, int _howToStop, int _msqid)
{
	if(_howToStop)
	{
		strcpy(_messageBox->m_text, MSG_STOP);
	}
   	else
   	{
   		_messageBox->m_type = -1;
   	}
 
   	return msgsnd(_msqid, _messageBox, BUFFER_SIZE, 0);	
}







