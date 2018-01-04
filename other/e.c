
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


typedef struct Input
{
	int m_cycels;
	int m_bufferSize;

}Input;

static int ParseUserInput(Input* _input, int argc, char **argv)
{
	int c;
	while ((c = getopt (argc, argv, "c: s:")) != -1)
	{
		switch (c)
		{
		case 'c':
			_input->m_second = atoi(optarg);
			break;
		case 's':
			_input->m_third = atoi(optarg);
			break;
		case '?':
			return 0;
		}
	}
	return 1;
}

void InsertToBuffer(int* _readbuffer, int _x, int _size)
{
	size_t i;
	
	for(i+0; i<_size; ++i)
	{
		_readbuffer[i] = _x;
	}
	return;
}


int main (int argc, char **argv)
{
	size_t i;
	int fd[2], numRead;
	Input input = {10, 10};
	pid_t childpid;
	int* readbuffer = NULL;


   	if(!ParseUserInput(&input, argc, argv))
    {
    	exit(EXIT_FAILURE);
    }
    
    readbuffer = malloc(input.m_bufferSize*sizeof(int));
    
    if(!readbuffer)
    {
    	exit(EXIT_FAILURE);
    }
    
	if((pipe(fd) == -1)
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
		close(fd[1]);
		for(;;)
		{
			sleep(2)
			numRead = read(pfd[0], readbuffer, input.m_bufferSize);
			if (numRead <= 0)
			{
				break;
			} 
			write(STDOUT_FILENO, readbuffer, numRead);
		}
		close(pd[1]);
		exit(0);
	}
	else
	{
		close(fd[0]);
		for(i=0; i< input.m_cycels; ++i)
		{
			sleep(1);
			InsertToBuffer(readbuffer, i, input.m_bufferSize);
			numRead = write(pfd[1], readbuffer, input.m_bufferSize);
			if (numRead <= 0)
			{
				break;
			}
		} 
		close(pfd[0]);
	}
	
	exit(EXIT_SUCCESS);
}




