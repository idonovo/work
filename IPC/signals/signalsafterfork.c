#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

typedef struct Input
{
	unsigned int m_first;
	unsigned int m_second;
	unsigned int m_third;	
}Input;

typedef void (*HandlerFunc)(int _sig, siginfo_t* _siginfo, void *context);

/******************************************************************************/
void HandlerParentFunc(int _sig, siginfo_t* _siginfo, void *context);
void HandlerChildFunc(int _sig, siginfo_t* _siginfo, void *context);
int ParseUserInput(Input* _input, int argc, char **argv);
int InitSigaction(struct sigaction* _sa1, Input* _input, HandlerFunc _handlerFunc);
/********************************************************************************/
void HandlerParentFunc(int _sig, siginfo_t* _siginfo, void *context)
{
    write(0, "ping!!\n", 32);
    return;
}

void HandlerChildFunc(int _sig, siginfo_t* _siginfo, void *context)
{
   write(0, "pong!!\n", 32);
   return;
}

int ParseUserInput(Input* _input, int argc, char **argv)
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

int InitSigaction(struct sigaction* _sa, Input* _input, HandlerFunc _handlerFunc)
{   
  	_sa->sa_sigaction = _handlerFunc;
    _sa->sa_flags = 0; 
    
    if(sigaction(_input->m_first, _sa, NULL) == -1)
    {
        return 0;
    }
    
    return 1;
}

/**************************************************************/
int main (int argc, char **argv)
{
  	Input input;
  	int childStatus;
  	struct sigaction sa1, sa2;
   
    if(!ParseUserInput(&input, argc, argv))
    {
    	return -1;
    }
    
   	childStatus = fork();
   	
    if(childStatus < 0)
    {
    	  return -1;
    }
    if(childStatus > 0)
    {
   		if(!InitSigaction(&sa1, &input, HandlerParentFunc))
   		{
   			return -1;
   		}  	
  		usleep(input.m_third);
  		printf("In parent proccess. my pid is: %d\n", (int)getpid());
		kill(childStatus,input.m_first);
		usleep(input.m_third);
		printf("Parent Goes to Sleep. my pid is: %d\n", (int)getpid());
  		pause();
		waitpid(-1, &childStatus, 0);
    }
  	else
  	{
    	if(!InitSigaction(&sa2, &input, HandlerChildFunc))
   		{
   			return -1;
   		}

    	printf("Child Goes to Sleep. my pid is: %d\n", (int)getpid());
    	pause();
    	usleep(input.m_third);
    	printf("child wake up. my pid is: %d\n", (int)getpid());
    	kill(getppid(), input.m_second);
    	exit(1);
  	}
	
  	return 0;
} 




