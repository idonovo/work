#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define PATH "pipes"
#define BUFFER_SIZE 64
#define DEFAULT_SIZE 10

int main (int argc, char **argv)
{

	int fd, numRead;
	char buffer[BUFFER_SIZE];

	if(-1 == mkfifo(PATH, S_IRUSR | S_IWUSR))
	{
		perror("fifo");
		exit(EXIT_FAILURE);
	}
	
    printf("In server\n consuming... \n please send somthing:\n");
    
    fd = open(PATH, O_RDONLY);
    if(fd == -1)
    {
        perror("open");
		exit(EXIT_FAILURE);
    }
    
    
   	for(;;)
    {
        numRead = read(fd, buffer, BUFFER_SIZE-10);
        if(numRead <= 0)
		{
			break;
		}
        sleep(1);
        write(STDOUT_FILENO, "recieved:", 10);
        write(STDOUT_FILENO,  buffer, BUFFER_SIZE-10);
		write(STDOUT_FILENO, "\n", 1);
    }
    return 0;
}
