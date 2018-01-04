
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


typedef union 
{
	struct
	{
		unsigned char ink		:4;
		unsigned char 			:1;	
		unsigned char paperjam 	:1;
		unsigned char empty		:1;	
		unsigned char standby 	:1;
	};
	unsigned char status;
} PrintStatus;

int main(){

    size_t i;
    FILE* fp = NULL;
    char buff[3];
	char* description[16] = {"all full", "b", "y", "b y", "m", "b m", "y  m", "b y m", "c", "b c", "b  y", "b y c", "m  c", "b m c", " c m y", "b y m c"}; 
	PrintStatus printStat;
	
	fp = fopen("file.txt", "w");
	
	if (NULL == fp)
	{
		return -1;
	}

	for (i =0; i <20; ++i)
	{
		fprintf(fp, "%d ", rand()%256);
	}
	
	fclose(fp);
		
	fp = fopen("file.txt", "w");
	
	if (NULL == fp)
	{
		return -1;
	}

	while(1)
	{			
		
		if(feof(fp))
		{
			break;
		}

		fgets(buff, 3, fp);
		printStat.status = (unsigned char)atoi(buff);
	
		if(printStat.ink)
		{
			printf("missing ink: %s\n", description[printStat.ink]);
		}
	
		if(printStat.paperjam)
		{
			printf("papar jam!!!\n");
		}
	
		if(printStat.empty)
		{
			printf("empty!! please insert pages\n");
		}
	
		if(printStat.standby)
		{
			printf("standby mode\n");
		}

		sleep(1);
	}
	
	fclose(fp);
	return 0;


}


