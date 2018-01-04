#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "../../inc/logger.h"
#include "../../inc/config.h"
#include "../../inc/HashMap.h"
#include "storeSubData.h"
#include "storeOptData.h"
#include "dealQuery.h"

#define LOG_WRITE(x, i)  LogWrite((x), (i), __func__, __LINE__, __FILE__, NULL);
#define REMOVE 1

struct OperatorsADT
{
	size_t				m_magic;
   	HashMap* 			m_hash;
   	LogData* 			m_logData;
};

struct Operator 
{
	unsigned int m_outgoingVoiceCall;
	unsigned int m_incomingVoiceCall;
	unsigned int m_outgoingSMS;
	unsigned int m_incomingSMS;
};

typedef struct OperatorKey 
{
	int m_tuple;
}OperatorKey;

/*****************************************************************/
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

/**********************************************************************************/   
/* i understand that in this stage singe query shuld be a print void function*/
static int PrintCdrSubscriber(const void* _key, void* data, void* _fp)
{
	fprintf((FILE*)_fp, "clinet number: %s\n outgoingWithinOperator: %u | incomingWithinOperator: %u| outgoingOutsideOperator: %u| incomingOutsideOperator: %u | outgoingSMSWithinOperator: %u | incomingSMSWithinOperator: %u | outgoingSMSOutsideOperator: %u | ncomingSMSOutsideOperator: %u | download: %u | upload: %u\n",  ((SubscriberKey*)_key)->m_msisdn, ((Subscriber*)data)->m_outgoingWithinOperator, ((Subscriber*)data)->m_incomingWithinOperator, ((Subscriber*)data)->m_outgoingOutsideOperator, ((Subscriber*)data)->m_incomingOutsideOperator, ((Subscriber*)data)->m_outgoingSMSWithinOperator, ((Subscriber*)data)->m_incomingSMSWithinOperator, ((Subscriber*)data)->m_outgoingSMSOutsideOperator, ((Subscriber*)data)->m_incomingSMSOutsideOperator, ((Subscriber*)data)->m_download, ((Subscriber*)data)->m_upload);
	return 0;
}

static int PrintCdrOperator(const void* _key, void* _data, void* _fp)
{
	fprintf((FILE*)_fp, "\noprator tuple: %d\n outgoingVoiceCall: %u | incomingVoiceCall: %u | outgoingSMS: %u | incomingSMS %u\n", ((OperatorKey*)_key)->m_tuple, ((Operator*)_data)->m_outgoingVoiceCall, ((Operator*)_data)->m_incomingVoiceCall, ((Operator*)_data)->m_outgoingSMS, ((Operator*)_data)->m_incomingSMS);
	return 0;	
}

static int DeleteSubscriberData(const void* _key, void* _data, void* _fp)
{
	memset(_data, 0, sizeof(Subscriber));
	return 0;
}


static int DeleteOperatorData(const void* _key, void* _data, void* _fp)
{
	memset(_data, 0, sizeof(Operator));
	return 0;	
}
/**********************************************************************************/
void SubscriberQuery(SubscribersADT* _adt, Query* _query)
{
	void* value;
	SubscriberKey key;
	
	if(!_query || !_adt)
	{
		return;
	}
	
	LOG_WRITE(_adt->m_logData, 1);
	strcpy(key.m_msisdn, _query->m_subscriberMSISDN);
	
	if(MAP_KEY_NOT_FOUND_ERROR == HashMapFind(_adt->m_hash, &key, (void*)&value))
	{
		return;
	}
	PrintCdrSubscriber(&key, value, stdout);
	return;
}

void OperatorQuery(OperatorsADT* _adt, Query* _query)
{
	void* value;
	OperatorKey key;
	
	if(!_query || !_adt)
	{
		return;
	}
	
	LOG_WRITE(_adt->m_logData, 1);
	key.m_tuple = _query->m_operatorTuple;
	
	if(MAP_KEY_NOT_FOUND_ERROR == HashMapFind(_adt->m_hash, &key, (void*)&value))
	{
		return;
	}
	PrintCdrOperator(&key, value, stdout);
	return;
}

int AllSubscribersReport(SubscribersADT* _adt, Query* _query)
{
	
	FILE* fp;
	size_t res;
	
	if(!_query || !_adt)
	{
		return -1;
	}
	LOG_WRITE(_adt->m_logData, 1);
	fp = fopen(_query->m_path, "a");
	if(!fp)
	{
		LOG_WRITE(_adt->m_logData, 5);
		return -1;
	}
	 
	res = HashMapForEach(_adt->m_hash, PrintCdrSubscriber, (void*)fp);
	
	if(res != HashMapSize(_adt->m_hash))
	{
		LOG_WRITE(_adt->m_logData, 5);
		return -1;
	}
	
	if(REMOVE == _query->m_removeFlag)
	{
		HashMapForEach(_adt->m_hash,  DeleteSubscriberData, NULL);
	}
	LOG_WRITE(_adt->m_logData, 1);
	return 0;
}

int AllOperatorsReport(OperatorsADT* _adt, Query* _query)
{
	FILE* fp;
	size_t res;
	
	if(!_query || !_adt)
	{
		return -1;
	}
	LOG_WRITE(_adt->m_logData, 1);
	fp = fopen(_query->m_path, "a");
	if(!fp)
	{
		LOG_WRITE(_adt->m_logData, 5);
		return -1;
	}
	 
	res = HashMapForEach(_adt->m_hash, PrintCdrOperator, (void*)fp);
	
	if(res != HashMapSize(_adt->m_hash))
	{
		LOG_WRITE(_adt->m_logData, 5);
		return -1;
	}
	
	if(REMOVE == _query->m_removeFlag)
	{
		HashMapForEach(_adt->m_hash, DeleteOperatorData, NULL);
	}
	
	LOG_WRITE(_adt->m_logData, 1);
	return 0;
}

int AggregateReport(SubscribersADT* _adtSubs, OperatorsADT* _adtOpts, Query* _query)
{
	if(!_query || !_adtSubs || !_adtOpts)
	{
		return -1;
	}
	LOG_WRITE(_adtSubs->m_logData, 1);
	
	if(AllSubscribersReport(_adtSubs, _query) != 0 || AllOperatorsReport(_adtOpts, _query) != 0)
	{
		LOG_WRITE(_adtSubs->m_logData, 5);
		return -1;
	}
	
	if(REMOVE == _query->m_removeFlag)
	{
		HashMapForEach(_adtSubs->m_hash,  DeleteSubscriberData, NULL);
	}
	
	if(REMOVE == _query->m_removeFlag)
	{
		HashMapForEach(_adtOpts->m_hash, DeleteOperatorData, NULL);
	}
	return 0;
}   


