#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define STRINGSIZE 128
#define PARAMETERSNUM 50

int readCommand(char* _string, char** _tokens){
	
	size_t i = 0;
	char* pch;
	
	nice();
	
	_tokens[i] = strtok(_string," \n");
	if (strcmp (_tokens[i], "exit") == 0)
	{
		return 1;
	}
	
	while(_tokens[i] != NULL)
	{
		++i;
		_tokens[i] = strtok(NULL, "-");
	}
	_tokens[i+1] = NULL;
	
	return 0;
}	

int main(){
	
	size_t isExit;
	char* string;
	char* tokens[PARAMETERSNUM];
	int forkParemeter, status;
	
	while(1)
	{
		printf("Ido Naveh shell command line:");
		fgets(string, STRINGSIZE, stdin);
		isExit = readCommand(string, tokens); 
	
		if(isExit)
		{
			return 0;
		}
	
		forkParemeter = fork();
	
		if (forkParemeter < 0)
		{
			printf("error code endeling\n");
			return -1;
		}
		else if (forkParemeter > 0)
		{
			waitpid(-1, &status, 0);	
		}
		else if(0 == forkParemeter)
		{
			execvp(tokens[0], tokens + 1);
			printf("error invaild command\n");
			exit(EXIT_FAILURE);	
		}

	}
	return 0;
}
	
	
	



	
