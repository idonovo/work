
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../inc/logger.h"

#define BUFFERSIZE 32

static void DefaultConfig(ConfigData* _confData);
static void ParsingFile(FILE* _fp , ConfigData* _confData);

void GetConfig(ConfigData* _confData, char* _confFileName)
{
	
	FILE* fp;
	
	DefaultConfig(_confData);
	
	if(!_confFileName)
	{
		return;
	}
	
	fp = fopen(_confFileName, "r");
	
	if(fp)
	{	
		ParsingFile(fp, _confData); 
	}
	
	fclose(fp);
	
	return;
}

static void DefaultConfig(ConfigData* _confData)
{
	strcpy(_confData->m_logFileName,"logger.txt");
	strcpy(_confData->m_modulName, "modul");  
	_confData->m_level = 'T';
	return; 
	
}

static void ParsingFile(FILE* _fp , ConfigData* _confData)
{

	char buffer1[BUFFERSIZE];
	char buffer2[BUFFERSIZE];
	char buffer3[BUFFERSIZE];
	 
	while (!feof(_fp))
	{
		
		fgets(buffer1, BUFFERSIZE, _fp);
		sscanf(buffer1,"[%[^]\n]",buffer2);
		if(strcmp(buffer2, "#") == 0)
		{
			
			while(!feof(_fp))
			{	
				sscanf(buffer1," \n%[^ =] = %[^\n]", buffer2, buffer3);
				
				if(strcmp(buffer2, "Level") == 0)
				{
					_confData->m_level = buffer3[4];
				}
				
				if(strcmp(buffer2, "File") == 0)
				{
				
					strcpy(_confData->m_logFileName, buffer3);
				}
				fgets(buffer1, BUFFERSIZE, _fp);
			}
		}
	}
	return;
}



