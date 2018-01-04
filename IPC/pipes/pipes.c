#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


typedef struct Input
{
	int m_cycels;
	int m_bufferSize;

}Input;

/************************************************************/
void ParseUserInput(Input* _input, int argc, char **argv);
void InsertToBuffer(char* _readbuffer, char _x, int _size);
void ChildRoutine(char* _buffer, int* _fd, int _size);
void ParentRoutine(char* _buffer, int* _fd, Input _input);
/************************************************************/

void ParseUserInput(Input* _input, int argc, char **argv)
{
	int c;
	
	_input->m_cycels = 10;
	_input->m_bufferSize = 10;
	
	while ((c = getopt (argc, argv, "c: s:")) != -1)
	{
		switch (c)
		{
		case 'c':
			_input->m_cycels = atoi(optarg);
			break;
		case 's':
			_input->m_bufferSize = atoi(optarg);
			break;
		default:
			fprintf (stderr, "\n invalid argument inserted \n");
			continue;
		}
	}
	
	fprintf (stderr,"Usage: %d [-c] %d[-s] \n", _input->m_cycels, _input->m_bufferSize);
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

void ChildRoutine(char* _buffer, int* _fd, int _size)
{
        int numRead;
        
        close(_fd[1]);
        
		for(;;)
		{
			usleep(200000);
			numRead = read(_fd[0], _buffer, _size);
    		if(numRead <= 0)
			{
				break;
			}
			write(STDOUT_FILENO, _buffer, numRead);
			write(STDOUT_FILENO, "\n", 1);
		}
		close(_fd[0]);
		exit(EXIT_SUCCESS);
}

void ParentRoutine(char* _buffer, int* _fd, Input _input)
{
        
        int i, numRead;
        
        close(_fd[0]);
		for(i=0; i< _input.m_cycels; ++i)
		{
			usleep(100000);
			InsertToBuffer(_buffer, (char)i+'A', _input.m_bufferSize);
			numRead = write(_fd[1], _buffer, _input.m_bufferSize);
			if(numRead <= 0)
			{
				break;
			}
		} 
		close(_fd[1]);
}

/***************************************/
int main (int argc, char **argv)
{
	size_t i;
	int fd[2], numRead;
	Input input;
	pid_t childpid;
	char* readBuffer;

 	ParseUserInput(&input, argc, argv);

    readBuffer = malloc(input.m_bufferSize*sizeof(char));
   
    if(!readBuffer)
    {
    	exit(EXIT_FAILURE);
    }
    
	if((pipe(fd) == -1))
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	
	if((childpid = fork()) == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if(childpid == 0)
	{
		ChildRoutine(readBuffer, fd, input.m_bufferSize);
	}
	else
	{
		 ParentRoutine(readBuffer, fd, input);
	}
	waitpid(-1, &childpid, 0);
	exit(EXIT_SUCCESS);
}


