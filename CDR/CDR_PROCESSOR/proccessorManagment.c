
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "proccessorManagment.h"


#define FAIL -1
/************************************************************************************/
void static GetDefalutConfig(ProcessorConfig* _config)
{
	strcpy(_config->m_feederPath, "/home/student/work/CDR/Feeder");
	_config->m_feederKey = 'f';
	_config->m_feederType = 1;
	strcpy(_config->m_queryPath, "/home/student/work/CDR/UI");	
	_config->m_queryKey = 'q';
	_config->m_queryType = 2;
	_config->m_size = 100000;
	return;
}	

void ReadConfig(char* _processorConfigFileName, ProcessorConfig* _config)
{
	return;
}

ManagmentData* CreateManagmentData(char* _processorConfigFileName)
{
	
	ManagmentData* managmentData;
	ProcessorConfig config;
	LogData* log = NULL;
	
	if(!_processorConfigFileName)
	{
		GetDefalutConfig(&config); 
	}
	else
	{
		ReadConfig(_processorConfigFileName, &config);
	}

	managmentData = malloc(sizeof(ManagmentData));
	if(!managmentData)
	{
		return NULL;
	}
	managmentData->m_shutDown = 0;
	log = GetLog(_processorConfigFileName);
	
	managmentData->m_feedrChannelData = CreateTransmissionChannel(config.m_feederPath, config.m_feederKey, config.m_feederType, log);
	if(!managmentData->m_feedrChannelData)
	{
		goto DESTROY_FEEDER_CHANNEL;
	}

	managmentData->m_queryChannelData = CreateTransmissionChannel(config.m_queryPath, config.m_queryKey, config.m_queryType, log);
	if(!managmentData->m_queryChannelData)
	{
		goto DESTROY_QI_CHANNEL;
	}

	managmentData->m_subscribersADT =CreateSubscribersADT(config.m_size, log);
	if(!managmentData->m_subscribersADT)
	{
		goto DESTROY_SUB_ADT;
	}
	
	managmentData->m_operatorsADT =CreateOperatorsADT(config.m_size, log);
	if(!managmentData->m_operatorsADT)
	{
		goto DESTROY_OPT_ADT;
	}
	return managmentData;

DESTROY_OPT_ADT:	
	DestroySubscribersADT(managmentData->m_subscribersADT);
DESTROY_SUB_ADT:
	DestroyChannel(managmentData->m_queryChannelData);
DESTROY_QI_CHANNEL:
	DestroyChannel(managmentData->m_feedrChannelData);
DESTROY_FEEDER_CHANNEL:
	free(managmentData);
	return NULL;
}

int ManagerRoutine(char* _configFile)
{
	ManagmentData* managmentData;
	pthread_t processor;
	pthread_t queryhandler;
	
    managmentData = CreateManagmentData(_configFile);
    
    for(;;)
    {
    	if(managmentData->m_shutDown == 1)
    	{
    		/* TODO SEND SHUT DOWN TO FEEDER */
    		return 0;
    	}
    	pthread_create(&processor, NULL, ProcessingRoutine, (void*)managmentData);
    	pthread_create(&queryhandler, NULL, QueryRoutine, (void*)managmentData);
	  	pthread_join(queryhandler,NULL);
	 	pthread_join(processor,NULL);
    }
    DestroyManagmentData(managmentData);
    return 0; 
}


void* ProcessingRoutine(void* _context)
{
	CdrData data = {0};
	int flag = 0;
	size_t i = 0;
	
	for(;;)
	{
		flag = ReadFromChannel((void*)&data, sizeof(CdrData), ((ManagmentData*)_context)->m_feedrChannelData);
		if(1 == flag)
		{
			pthread_exit(NULL);
		}
		printf("%d insert", ++i);
		InsertToOperatorsADT(((ManagmentData*)_context)->m_operatorsADT, &data);
		InsertToSubscribersADT(((ManagmentData*)_context)->m_subscribersADT,&data);
		memset(&data, 0, sizeof(CdrData));	
	}
	pthread_exit(NULL);
}


void* QueryRoutine(void* _context)  
{
	Query query;
	int flag = 0;
	
	for(;;)
	{
		ReadFromChannelWithWait((void*)&query, sizeof(Query), ((ManagmentData*)_context)->m_queryChannelData);
		
		if(1 == flag)
		{
			pthread_exit(NULL);
		}
		
		switch(query.m_enum)
		{
			case 1:
				SubscriberQuery( ((ManagmentData*)_context)->m_subscribersADT, &query);
				break;	
			case 2:
				OperatorQuery( ((ManagmentData*)_context)->m_operatorsADT, &query);
				break;
			case 3:
				AllSubscribersReport( ((ManagmentData*)_context)->m_subscribersADT, &query);
				break;
			case 4:
				AllOperatorsReport( ((ManagmentData*)_context)->m_operatorsADT, &query);
				break;
			case 5:	
				AggregateReport( ((ManagmentData*)_context)->m_subscribersADT,  ((ManagmentData*)_context)->m_operatorsADT, &query);
				break;
			case 6:
				((ManagmentData*)_context)->m_shutDown = 1;
				pthread_exit(NULL);
		}
	}
	pthread_exit(NULL);
}

/* destroy function */
void DestroyManagmentData(ManagmentData* _managmentData)
{
	if(!_managmentData)
	{
		return;
	}
	
	DestroyOperatorsADT(_managmentData->m_operatorsADT);
	DestroySubscribersADT(_managmentData->m_subscribersADT);
	DestroyChannel(_managmentData->m_feedrChannelData);
	DestroyChannel(_managmentData->m_queryChannelData);
	free(_managmentData);
	return;
}
