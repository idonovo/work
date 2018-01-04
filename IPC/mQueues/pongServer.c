#include "mqueues.h"

int main (int argc, char **argv)
{
	int key, msqid;
	Input input;
	MessageBox messageBox;
	char buffer[BUFFER_SIZE];
	
	ParseInput(&input, argc, argv);
	
	key = ftok(QUEUE_FILENAME, QUEUE_ID);
	
	if(FAIL == key)
	{
		perror("ftok");
	    exit(EXIT_FAILURE);
	}
	
	msqid = msgget(key, 0666 | IPC_CREAT);
	
	if(FAIL == msqid)
	{
		perror("msgget");
	    exit(EXIT_FAILURE);
	}
	
	printf("Lets start reading:");
	
	for(;;)
	{    
       	if(FAIL == msgrcv(msqid, &messageBox, sizeof(messageBox.m_text), 0, 0)) 
       	{
            perror("msgrcv");
            exit(1);
        }
        
       	if(input.m_verb)
       	{
			printf("\"%s\"\n", messageBox.m_text);
       	}
       	
       	if(IsLastMessage(&messageBox))
       	{
       		printf("finish!!\n");
       		break;
       	}
       		
       	InsertToBuffer(buffer, (char)'A', BUFFER_SIZE);
		if(input.m_verb)
       	{
			printf("\"%s\"\n", buffer);
       	}
		InitMessageBox(&messageBox, buffer, getpid());
		msgsnd(msqid, &messageBox, BUFFER_SIZE, 0);
       	
       	if(input.m_speed)
       	{
   	    	sleep(input.m_speed);    	
       	}
    }
    return 0;
}

