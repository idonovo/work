#include "mqueues.h"


int main (int argc, char **argv)
{
	int key, msqid, send, i;
	char buffer[BUFFER_SIZE];
	Input input;
	MessageBox messageBox;
	
	ParseInput(&input, argc, argv);
	
	key = ftok(QUEUE_FILENAME, QUEUE_ID);
	if(FAIL == key)
	{
		perror("ftok");
	    exit(EXIT_FAILURE);
	}
	
	msqid = CreateQueue(key, input.m_create);
	
	if(FAIL == msqid)
	{
		perror("msgget");
	    exit(EXIT_FAILURE);
	}
	
	printf("Lest start sending:\n");
	
	for(i=0; i <= input.m_nCycels; ++i)
	{
		
		if(i == input.m_nCycels)
		{
			if(FAIL == SendEOF(&messageBox, input.m_howToStop, msqid))
			{
				perror("msgsnd");
	    		exit(EXIT_FAILURE);
			}
			break;	
		}
		
		InsertToBuffer(buffer, (char)i + 'A', BUFFER_SIZE);
		if(input.m_verb)
       	{
			printf("\"%s\"\n", buffer);
       	}
       	
		InitMessageBox(&messageBox, buffer, getpid());
		send = msgsnd(msqid, &messageBox, BUFFER_SIZE, 0);
		
		if(FAIL == send)
		{
			perror("msgsnd");
	    	exit(EXIT_FAILURE);
		}
		
		if(input.m_speed)
       	{
   	    	sleep(input.m_speed);    	
       	}
       	
       	if(FAIL == msgrcv(msqid, &messageBox, sizeof(messageBox.m_text), 1, 0)) 
       	{
            perror("msgrcv");
            exit(1);
        }
        
       	if(input.m_verb)
       	{
			printf("\"%s\"\n", messageBox.m_text);
       	}
	}
	
    if(input.m_destroy)
    {
    	msgctl(msqid, IPC_RMID, NULL);
    }
   
    return 0;
}
