

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h> 
#include <fcntl.h>
 
int main(){

	
	int fd;
	void* read;

	fd = open("./shared.txt", O_RDWR);
	read = mmap((caddr_t)0, 100, 0666, MAP_SHARED , fd, 0);
	strcpy((char*)read, "my name is intigo montoya");
	printf("%s\n", ((char*)read));
	
	return 0;
	
}

