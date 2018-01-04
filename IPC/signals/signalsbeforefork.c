#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

typedef struct Input
{
	int m_first;
	int m_second;
	int m_third;
	
}Input;

/******************************************************************************/
void HandlerFunc(int _sig, siginfo_t* _siginfo, void *context);
int ParseUserInput(Input* _input, int argc, char **argv);
int InitSigaction(struct sigaction* _sa1, Input* _input);
/********************************************************************************/
static void HandlerFunc(int _sig, siginfo_t* _siginfo, void *context)
{
    printf("Signal %d ping!!\n",  _sig);
    return;
}

static int ParseUserInput(Input* _input, int argc, char **argv)
{
	int c;
	while ((c = getopt (argc, argv, "p: c: s:")) != -1)
	{
		switch (c)
		{
		case 'p':
			_input->m_first = atoi(optarg);
			break;
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

int InitSigaction(struct sigaction* _sa1, Input* _input)
{
    
  	_sa1->sa_sigaction = HandlerFunc;
    _sa1->sa_flags = 0; 
    
    if(sigaction(_input->m_first, &(*_sa1), NULL) == -1)
    {
        return -1;
    }
    
    return 0;
}

/**************************************************************/
int main (int argc, char **argv)
{
  	Input input;
  	int childStatus;
  	struct sigaction sa1;
   
   	if(!ParseUserInput(&input, argc, argv))
    {
    	return -1;
    }
    
   	if(InitSigaction(&sa1, &input) == -1)
   	{
   		return -1;
   	} 
    
   	childStatus = fork();
    
    if(childStatus < 0)
    {
    	  exit(1);
    }
    if(childStatus > 0)
    {
  		usleep(2000);
  		printf("In parent proccess. my pid is: %d\n", (int)getpid());
		kill(childStatus,input.m_first);
		usleep(2000);
		printf("Father Goes to Sleep. my pid is: %d\n", (int)getpid());
  		pause();
		waitpid(-1, &childStatus, 0);
    }
  	else
  	{
    	printf("Child Goes to Sleep. my pid is: %d\n", (int)getpid());
    	pause();
    	usleep(2000);
    	printf("child wake up. my pid is: %d\n", (int)getpid());
    	kill(getppid(), input.m_first);
    	exit(1);
  	}
	
  	return 0;
} 




