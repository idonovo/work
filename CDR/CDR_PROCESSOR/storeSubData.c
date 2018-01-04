#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "../../inc/HashMap.h"
#include "storeSubData.h"

#define LOG_WRITE(x, i)  LogWrite((x), (i), __func__, __LINE__, __FILE__, NULL);
#define FAIL -1
#define EMPTY 0
#define MAGIC  0xddddc



struct SubscribersADT
{
	size_t				m_magic;
   	HashMap* 			m_hash;
   	LogData* 			m_logData;
};

struct Subscriber 
{
	unsigned int m_outgoingWithinOperator;
	unsigned int m_incomingWithinOperator;
	unsigned int m_outgoingOutsideOperator;
	unsigned int m_incomingOutsideOperator;
	unsigned int m_outgoingSMSWithinOperator;
	unsigned int m_incomingSMSWithinOperator;
	unsigned int m_outgoingSMSOutsideOperator;
	unsigned int m_incomingSMSOutsideOperator;
	unsigned int m_download;
	unsigned int m_upload;
};

typedef struct SubscriberKey 
{
	 char	m_msisdn[16];
}SubscriberKey;

/********************************************************************/
static int SubscriberEqualityFunction(const void* _firstKey, const void* _secondKey);

static size_t SubscriberHash(const void* _key);

static Subscriber* CreateSubscriber(CdrData* _data);

static int InsertDataToSubscriber(Subscriber* _subscriber, CdrData* _data);

void static keyDestroy(void* _key);

void static SubscriberDestroy(void* _key);
/**************************************************************************************/
static int SubscriberEqualityFunction(const void* _firstKey, const void* _secondKey)
{
	return strcmp(((SubscriberKey*)_firstKey)->m_msisdn, ((SubscriberKey*)_secondKey)->m_msisdn) == 0 ? 1 : 0;
}

static size_t SubscriberHash(const void* _key)
{
    unsigned long hash = 5381;
    int c, i =0;

    while (0 != (c = ((SubscriberKey*)_key)->m_msisdn[i]))
    {
        hash = ((hash << 5) + hash) + c; 
        ++i;
    }

    return (size_t)hash;
}

void static keyDestroy(void* _key)
{
	free(_key);
}

void static SubscriberDestroy(void* _subscriber)
{
	free(_subscriber);
}
/**********************************************************************************/
static Subscriber* CreateSubscriber(CdrData* _data)
{
	Subscriber* subscriber;
	subscriber = calloc(1, sizeof(Subscriber));
	
	if(!subscriber)
	{
		return NULL;
	}
	
	InsertDataToSubscriber(subscriber, _data);
	return subscriber;
} 

static int InsertDataToSubscriber(Subscriber* _subscriber, CdrData* _data)
{	
	switch (_data->m_ParOprator)
		{
		case 'a':
			switch (_data->m_type)
				{
				case 'a':
				_subscriber->m_outgoingWithinOperator +=  _data->m_duration;
				case 'b':
				_subscriber->m_incomingWithinOperator +=  _data->m_duration;
				case 'c':
				++_subscriber->m_incomingSMSWithinOperator;
				case 'd':
				++_subscriber->m_outgoingSMSWithinOperator;
				}
		case 'b':
			switch (_data->m_type)
				{
				case 'a':
				_subscriber->m_outgoingOutsideOperator +=  _data->m_duration;
				case 'b':
				_subscriber->m_incomingOutsideOperator +=  _data->m_duration;
				case 'c':
				++_subscriber->m_incomingSMSOutsideOperator;
				case 'd':
				++_subscriber->m_outgoingSMSOutsideOperator;
				}
		default:
			 	_subscriber->m_download += _data->m_downloaded;
				_subscriber->m_upload += _data->m_uploaded;		
		}

	return 0;
}
/*****************************************************************************************/ 
SubscribersADT* CreateSubscribersADT(size_t _size, LogData* _logData)
{
	SubscribersADT* subscribersADT;
	
	subscribersADT = malloc(sizeof(SubscribersADT));
	if(!subscribersADT)
	{

		return NULL;
	}
	
	subscribersADT->m_logData =_logData;
	
	LOG_WRITE(subscribersADT->m_logData, 1);
	
	subscribersADT->m_hash = HashMapCreate(_size, SubscriberHash, SubscriberEqualityFunction);
	if(!subscribersADT->m_hash)
	{
		LOG_WRITE(subscribersADT->m_logData, 5)
		goto DESTROY_SUB_ADT;
	}
	
	subscribersADT->m_magic = MAGIC;
	
	LOG_WRITE(subscribersADT->m_logData, 1)
	return subscribersADT;

DESTROY_SUB_ADT:
	free(subscribersADT);
	return NULL;
}

int InsertToSubscribersADT(SubscribersADT* _adt, CdrData* _data)
{
	SubscriberKey* key;
	Subscriber* subscriber; 
	
	LOG_WRITE(_adt->m_logData, 1)
	
	if(!_adt || !_data)
	{
		
		LOG_WRITE(_adt->m_logData, 5)
		return FAIL;
	}

	key = malloc(sizeof(SubscriberKey));
	
	if(!key)
	{
		LOG_WRITE(_adt->m_logData, 5)
		return FAIL;
	}
	
	strcpy(key->m_msisdn, _data->m_msidn);
	
	if(MAP_KEY_NOT_FOUND_ERROR == HashMapAction(_adt->m_hash,(void*)key, InsertDataToSubscriber,_data))
	{
		subscriber = CreateSubscriber(_data);
		if(subscriber)
		{
       		LOG_WRITE(_adt->m_logData, 1)
       		return HashMapInsert(_adt->m_hash, (void*)key, (void*)subscriber);
		}
		LOG_WRITE(_adt->m_logData, 5)
		return FAIL;	
	}
	
	free(key);
	LOG_WRITE(_adt->m_logData, 1)
	return 0;
}

void DestroySubscribersADT(SubscribersADT* _adt)
{
    if(!_adt)
    {
    	return;
    }
	LOG_WRITE(_adt->m_logData, 1)
	
    HashMapDestroy(&_adt->m_hash, keyDestroy, SubscriberDestroy);
	free(_adt);
	return;
}



