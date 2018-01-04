#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "../../inc/logger.h"
#include "../../inc/config.h"
#include "../../inc/HashMap.h"
#include "storeOptData.h"


#define LOG_WRITE(x, i)  LogWrite((x), (i), __func__, __LINE__, __FILE__, NULL);
#define FAIL -1
#define EMPTY 0
#define MAGIC  0xddddc

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

/********************************************************************/
static int OperatorEqualityFunction(const void* _firstKey, const void* _secondKey);

static size_t OperatorHash(const void* _key);

static Operator* CreateOperator(CdrData* _data);

static int InsertDataToOperator(Operator* _operator,  CdrData* _data);

void static keyDestroy(void* _key);

void static OperatorDestroy(void* _operator);
/**************************************************************************************/

static int OperatorEqualityFunction(const void* _firstKey, const void* _secondKey)
{
	return ((OperatorKey*)_firstKey)->m_tuple == ((OperatorKey*)_secondKey)->m_tuple ? 1 : 0;
}

static size_t OperatorHash(const void* _key)
{
    return (size_t)((OperatorKey*)_key)->m_tuple;
}

void static keyDestroy(void* _key)
{
	free(_key);
}

void static OperatorDestroy(void* _operator)
{
	free(_operator);
}
/*************************************************************************************************/
static Operator* CreateOperator(CdrData* _data)
{
	Operator* operator;
	operator = calloc(1, sizeof(Operator));
	
	if(!operator)
	{
		return NULL;
	}
	
	InsertDataToOperator(operator, _data);
	
	return operator;
}
 
static int InsertDataToOperator(Operator* _operator, CdrData* _data)
{
	switch (_data->m_type)
	{
		case 'a':
		_operator->m_outgoingVoiceCall += _data->m_duration;
		case 'b':
		_operator->m_incomingVoiceCall += _data->m_duration;
		case 'c':
		++_operator->m_outgoingSMS;
		case 'd':
		++_operator->m_incomingSMS;
	}
	
	return 0;
}
/**********************************************************************************/
OperatorsADT* CreateOperatorsADT(size_t _size, LogData* _logData)
{
	OperatorsADT* operatorsADT;
	
	operatorsADT = malloc(sizeof(OperatorsADT));
	if(!operatorsADT)
	{
		return NULL;
	}
	
	operatorsADT->m_logData = _logData;
	LOG_WRITE(operatorsADT->m_logData, 1);
	
	operatorsADT->m_hash = HashMapCreate(_size, OperatorHash, OperatorEqualityFunction);
	if(!operatorsADT->m_hash)
	{
		LOG_WRITE(operatorsADT->m_logData, 5);
		goto DESTROY_OPT_ADT;
	}
	
	operatorsADT->m_magic = MAGIC;
	LOG_WRITE(operatorsADT->m_logData, 1);
	return operatorsADT;

DESTROY_OPT_ADT:
	free(operatorsADT);
	return NULL;
}

/************************************************************************/
int InsertToOperatorsADT(OperatorsADT* _adt, CdrData* _data)
{
    OperatorKey* key;
	Operator* operator = NULL;
	
	LOG_WRITE(_adt->m_logData, 1);
	
	if(!_adt || !_data)
	{
		return FAIL;
	}
	
	key = malloc(sizeof(OperatorKey));
	
	if(!key)
	{
		return FAIL;
	}
	
	key->m_tuple = _data->m_ParOpratorTuple;
	
	if(MAP_KEY_NOT_FOUND_ERROR == HashMapAction(_adt->m_hash,(void*)key, InsertDataToOperator, _data))
	{
		operator = CreateOperator(_data);
		if(operator)
		{
       		LOG_WRITE(_adt->m_logData, 1)
       		return HashMapInsert(_adt->m_hash, (void*)key, (void*)operator);
		}
		LOG_WRITE(_adt->m_logData, 5)
		return FAIL;	
	}	
	free(key);
	LOG_WRITE(_adt->m_logData, 1)
	return 0;
}

void DestroyOperatorsADT(OperatorsADT* _adt)
{

	
	if(!_adt)
	{
		return;
	}
    HashMapDestroy(&_adt->m_hash, keyDestroy, OperatorDestroy);
	free(_adt);
	return;
}



