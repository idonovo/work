#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
 
#define PATH "pipes"
#define BUFFER_SIZE 64
#define DEFAULT_SIZE 10


typedef struct Input
{
	int m_cycels;

}Input;

/*************************************************************************/
void InsertToBuffer(char* _readbuffer, char _x, int _size);
void ParseUserInput(Input* _input, int argc, char **argv);
/*************************************************************************/

void ParseUserInput(Input* _input, int argc, char **argv)
{
	int c;
	
	_input->m_cycels =  DEFAULT_SIZE;
	
	while ((c = getopt (argc, argv, "c:")) != -1)
	{
		if(c == 'c')
		{
			_input->m_cycels = atoi(optarg);
		}
		else
		{
			fprintf (stderr, "\n invalid argument inserted \n");
			continue;
		}
	}
	
	fprintf (stderr,"Usage: %d [-c]  \n", _input->m_cycels);
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

/**********************************************************/
int main (int argc, char **argv)
{

	Input input;
	int fd, i;
	char buffer[BUFFER_SIZE];
	
	ParseUserInput(&input, argc, argv);
	
    printf("In client\n sending input... \n");
    
    fd = open(PATH, O_WRONLY);
    if(fd == -1)
    {
        perror("open");
	    exit(EXIT_FAILURE);
    }
    
   	for(i = 0; i < input.m_cycels; ++i)
    {    
        InsertToBuffer(buffer, i+'A', BUFFER_SIZE); 
        write(fd, buffer, BUFFER_SIZE);
    }
    
    close(fd);
    return 0;
}
