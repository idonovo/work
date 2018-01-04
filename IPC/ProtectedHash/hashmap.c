#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#include "../../inc/HashMap.h"
#include "../../inc/list_itr.h"
#include "../../inc/list_functions.h"

#define MAGIC  0xddddd
#define MUTEX_DEFAULT_SIZE 100
#define LIST_END(L)   (&(L)->m_tail)
#define IS_A_LIST(L)  ((L) && (L)->m_magic == MAGIC) 
#define SUCCESS 0


typedef struct Data Data;

typedef struct FindKey FindKey;

typedef List Bucket;

struct Data
{
	void* m_value;
	void* m_key;
};

struct  HashMap
{
    Bucket** 			m_bucket;
   	HashFunction 		m_hashFunc;
   	EqualityFunction 	m_keysEqualFunc; 
   	pthread_mutex_t		m_mutexArray[100];	
    size_t 	m_magic;
    size_t 	m_hashSize;
    size_t 	m_nItems;

};

struct FindKey
{
    void* 	m_key;
   	EqualityFunction m_keysEqualFunc; 	
};

static size_t FindPrime(size_t _number);
static HashMap* InitialHash(HashMap* _newHash, size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc);
static void BucketDestroy(Bucket* _list, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value));
size_t ForEachList(Bucket* _list, KeyValueActionFunction _action, void* _context);
static int Predicate(void* _key, void* _find);
static ListItr IsKeyFound(Bucket* _bucket, const void* _key, EqualityFunction _keysEqualFunc);
static int CreateDataNode(Bucket* _bucket, const void* _key, const void* _value);
static void	ExtractKeyAndValue(HashMap *_map, Data** _tempArray);
static size_t FindChains(const HashMap* _map);
static size_t FindLongestChain(const HashMap* _map);

/********************************************************************************************************/
static HashMap* InitialHash(HashMap* _newHash, size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	size_t i, j, y;
	
	_newHash->m_bucket = malloc(_capacity*sizeof(Bucket*));
	if(NULL == _newHash->m_bucket)
	{
		goto DESTROY_BUCKET;
	}
	
	for(i = 0; i < MUTEX_DEFAULT_SIZE; ++i)
	{
		if(0 != pthread_mutex_init(&_newHash->m_mutexArray[i], NULL))
		{
			y = i;
			goto DESTROYMUTEXES;
		}
	}
	 
	_capacity = FindPrime(_capacity);
	
	for(i = 0; i < _capacity; ++i)
	{
		_newHash->m_bucket[i] = ListCreate();
		if(NULL == _newHash->m_bucket[i])
		{
			goto DESTROYBUCKETS;
		}
	}
	
	_newHash->m_magic = MAGIC;
	_newHash->m_hashSize = _capacity;
	_newHash->m_nItems = 0;
   	_newHash->m_hashFunc = _hashFunc;
   	_newHash->m_keysEqualFunc = _keysEqualFunc; 
   	
	return _newHash;
	
DESTROYBUCKETS:
	for(j = 0; j < i; ++j)
	{
		ListDestroy(&_newHash->m_bucket[j], NULL);
	}
DESTROYMUTEXES:
	for(j = 0; j < y; ++j)
	{
		pthread_mutex_destroy(&_newHash->m_mutexArray[j]);
	}
DESTROYMUTEXARRAY:
	free(_newHash->m_mutexArray);
DESTROY_BUCKET:
	free(_newHash->m_bucket);
	free(_newHash);
	return NULL;
} 

static size_t FindPrime(size_t _number){
	
	size_t i;
	
	while(1)
	{	
		for(i=2; i< (_number/2); i++)
		{
			if(_number%i == 0)
			{
				_number++;
				break;
			}
		}
		return _number;
	}
}

HashMap* HashMapCreate(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc){

	HashMap* newHash;
	
	if(NULL == _hashFunc || NULL == _keysEqualFunc)
	{
		return NULL;
	}
	
	newHash = malloc(sizeof(HashMap));
	if(!newHash)
	{
		return NULL;
	}	
	
	newHash = InitialHash(newHash, _capacity,  _hashFunc, _keysEqualFunc);
   	
   	return newHash;
}
/***********************************************************************/
static void BucketDestroy(Bucket* _list, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value)){
	
	void* item = NULL;

	while(!ListIsEmpty(_list))
	{		
		ListPopTail(_list, &item);
		
		if( NULL != _keyDestroy)
		{
			_keyDestroy(((Data*)item)->m_key);
		}
			
		if( NULL != _valDestroy)
		{
			_valDestroy(((Data*)item)->m_value);
		}
		free(item);
	}	
	return;	
}

void HashMapDestroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value)){

	size_t i, j;
	
	if(!IS_A_LIST(*_map))
	{
		return;
	}
	
	for(i = 0; i < (*_map)->m_hashSize; ++i)
	{
		BucketDestroy((*_map)->m_bucket[i], _keyDestroy, _valDestroy);		
		free((*_map)->m_bucket[i]);
	}
	
	for(j = 0; j < (*_map)->m_hashSize; ++j)
	{
			pthread_mutex_destroy(&(*_map)->m_mutexArray[j]);
	}
	
	free((*_map)->m_bucket);
	free(*_map);
	(*_map) = NULL;
	return;
}
/***********************************************************************/
static void	ExtractKeyAndValue(HashMap *_map, Data** _tempArray)
{
    
    size_t i, x = 0;
	void* item = NULL;
	
    for(i = 0; i < _map->m_hashSize; ++i)
	{	   
	    while(!ListIsEmpty(_map->m_bucket[i]))
	    {
	    	ListPopHead(_map->m_bucket[i], &item);
	    	_tempArray[x] = item;
	    	++x;
	    }
    }
    return;
}

Map_Result HashMapRehash(HashMap *_map, size_t newCapacity)
{

    Data** tempArray;
    size_t i, size;
    
    if(!IS_A_LIST(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	tempArray = malloc((_map->m_nItems)*sizeof(Data*));	
	if(!tempArray)
	{
	    return MAP_ALLOCATION_ERROR;
	}
	
	size = _map->m_nItems;
	
	/* removing the buckets */ 
	ExtractKeyAndValue(_map, tempArray);
	BucketDestroy(*_map->m_bucket, NULL, NULL);	
	free(_map->m_bucket);
	
	if(!InitialHash(_map, newCapacity, _map->m_hashFunc, _map->m_keysEqualFunc))
	{
		return MAP_ALLOCATION_ERROR;
	}
	
	for(i = 0; i < size; ++i)
	{
	    HashMapInsert(_map, tempArray[i]->m_key, tempArray[i]->m_value);
	}
	free(tempArray);
	
	return MAP_SUCCESS;
}

/***********************************************************************/
static int Predicate(void* _value, void* _find)
{
	return ((FindKey*)_find)->m_keysEqualFunc(((Data*)_value)->m_key, ((FindKey*)_find)->m_key);

}

static ListItr IsKeyFound(Bucket* _bucket, const void* _key, EqualityFunction _keysEqualFunc)
{

	ListItr endIter;
	ListItr curIter;
	FindKey find;
	find.m_key = (void*)_key; 
	find.m_keysEqualFunc = _keysEqualFunc;
	
	curIter = ListItr_Begin(_bucket);
	endIter = ListItr_End(_bucket);
	curIter = ListItr_FindFirst(curIter, endIter, Predicate, (void*)&find);
	
	return curIter;
}

static int CreateDataNode(Bucket* _bucket, const void* _key, const void* _value)
{
	Data* newDataNode = malloc(sizeof(Data));
	if(NULL == newDataNode)
	{
		return 0;
	}
	
	newDataNode->m_key = (void*)_key;
	newDataNode->m_value =(void*) _value;
	
	if(ListPushHead(_bucket, newDataNode) != LIST_OK)
	{
		return 0;
	}
	
	return 1;
}

Map_Result HashMapInsert(HashMap* _map, const void* _key, const void* _value)
{

	size_t listIndex, mutexIndex;
	ListItr curIter;
	
	if(!IS_A_LIST(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(NULL == _key)
	{
		return MAP_KEY_NULL_ERROR;
	}

	listIndex = _map->m_hashFunc(_key)%_map->m_hashSize;
	
	mutexIndex = listIndex % MUTEX_DEFAULT_SIZE;
	
	pthread_mutex_lock(&_map->m_mutexArray[mutexIndex]); 
	
	curIter = IsKeyFound(_map->m_bucket[listIndex], _key, _map->m_keysEqualFunc);
	
	if(curIter != ListItr_End(_map->m_bucket[listIndex]))
	{
		pthread_mutex_unlock(&_map->m_mutexArray[mutexIndex]);
		return MAP_KEY_DUPLICATE_ERROR;
	}

	if(CreateDataNode(_map->m_bucket[listIndex], _key, _value))
	{
		++_map->m_nItems;
		pthread_mutex_unlock(&_map->m_mutexArray[mutexIndex]);
		return MAP_SUCCESS;
	}
	
	pthread_mutex_unlock(&_map->m_mutexArray[mutexIndex]);
	return MAP_ALLOCATION_ERROR;
	
}
/***********************************************************************/

size_t HashMapForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{

	size_t i, mutexIndex, numOfIter = 0;
	
	if(NULL == _map || NULL ==_action)
	{
		return 0;
	}
	
	for(i = 0; i < _map->m_hashSize; ++i)
	{	
		 mutexIndex = i % MUTEX_DEFAULT_SIZE;
	
		pthread_mutex_lock(&_map->m_mutexArray[mutexIndex]); 
		numOfIter += ForEachList(_map->m_bucket[i], _action, _context);
		pthread_mutex_unlock(&_map->m_mutexArray[mutexIndex]);
	}
	return numOfIter;
}

size_t ForEachList(Bucket* _list, KeyValueActionFunction _action, void* _context)
{
	
	size_t i;
	ListItr endIter;
	ListItr curIter;
	void* item = NULL;
	
	curIter = ListItr_Begin(_list);
	endIter = ListItr_End(_list);
	i = 0;
	
	while(curIter != endIter)
	{	
		item = ListItr_Get(curIter);
		if(NULL != ((Data*)item)->m_key)
		{
			_action(((Data*)item)->m_key, ((Data*)item)->m_value, _context);
		}
		curIter = ListItr_Next(curIter);
		++i;
	}	
	return i;		
}

/**********************************************************************************/
Map_Result HashMapRemove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{

    size_t listIndex, mutexIndex;
	ListItr curIter;
	
	if(!IS_A_LIST(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(NULL == _searchKey)
	{
		return MAP_KEY_NULL_ERROR;
	}

	listIndex = _map->m_hashFunc(_searchKey)%_map->m_hashSize;
	mutexIndex = listIndex%MUTEX_DEFAULT_SIZE;
	
	pthread_mutex_lock(&_map->m_mutexArray[mutexIndex]); 
	
	curIter = IsKeyFound(_map->m_bucket[listIndex], _searchKey, _map->m_keysEqualFunc);
	
	if(curIter == ListItr_End(_map->m_bucket[listIndex]))
	{
		pthread_mutex_unlock(&_map->m_mutexArray[mutexIndex]);
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	
	curIter= ListItr_Remove(curIter);
    *_pKey = ((Data*)curIter)->m_key;
    *_pValue = ((Data*)curIter)->m_value;
    --_map->m_nItems;
    pthread_mutex_unlock(&_map->m_mutexArray[mutexIndex]);
    return MAP_SUCCESS;
}
/*****************************************************************************************/

Map_Result HashMapFind(const HashMap* _map, const void* _searchKey, void** _pValue)
{

	size_t listIndex, mutexIndex;
	ListItr curIter;
	
	if(!IS_A_LIST(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(NULL == _searchKey)
	{
		return MAP_KEY_NULL_ERROR;
	}

	listIndex = _map->m_hashFunc(_searchKey)%_map->m_hashSize;
	
	mutexIndex = listIndex%MUTEX_DEFAULT_SIZE;
	
	pthread_mutex_lock(&_map->m_mutexArray[mutexIndex]); 
	
	curIter = IsKeyFound(_map->m_bucket[listIndex], _searchKey, _map->m_keysEqualFunc);
	
	if(curIter == ListItr_End(_map->m_bucket[listIndex]))
	{
		pthread_mutex_unlock(&_map->m_mutexArray[mutexIndex]);
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	
	curIter = ListItr_Get(curIter);
	*_pValue = ((Data*)curIter)->m_value;
	pthread_mutex_unlock(&_map->m_mutexArray[mutexIndex]);
	return MAP_SUCCESS;
}

Map_Result HashMapAction(const HashMap* _map, const void* _searchKey, ActionFunction _action, void* _context)
{
	
	size_t listIndex, mutexIndex;
	ListItr curIter;
	
	if(!IS_A_LIST(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(NULL == _searchKey || NULL == _action)
	{
		return MAP_KEY_NULL_ERROR;
	}

	listIndex = _map->m_hashFunc(_searchKey)%_map->m_hashSize;
	
	mutexIndex = listIndex%MUTEX_DEFAULT_SIZE;
	
	pthread_mutex_lock(&_map->m_mutexArray[mutexIndex]); 
	
	curIter = IsKeyFound(_map->m_bucket[listIndex], _searchKey, _map->m_keysEqualFunc);
	
	if(curIter == ListItr_End(_map->m_bucket[listIndex]))
	{
		pthread_mutex_unlock(&_map->m_mutexArray[mutexIndex]);
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	
	curIter = ListItr_Get(curIter);
	if(SUCCESS ==_action(((Data*)curIter)->m_value, _context))
	{
		pthread_mutex_unlock(&_map->m_mutexArray[mutexIndex]);
		return MAP_SUCCESS;	
	}
	pthread_mutex_unlock(&_map->m_mutexArray[mutexIndex]);
	return MAP_FAILURE;	

}

/*********************************************************************************************/
size_t HashMapSize(const HashMap* _map)
{

	if(!IS_A_LIST(_map))
	{
		return 0;
	}
	return  _map->m_nItems;

}
/*************************************************************************************/
Map_Stats HashMapGetStatistics(const HashMap* _map)
{


	Map_Stats mapStats;
	 
	if(!IS_A_LIST(_map) || _map->m_nItems == 0)
	{
		return mapStats;
	}
	
	mapStats.pairs = HashMapSize(_map);
	mapStats.buckets = _map->m_hashSize;
	mapStats.chains = FindChains(_map);
   	mapStats.collisions = mapStats.pairs - mapStats.chains;
   	mapStats.maxChainLength = FindLongestChain(_map);
   	mapStats.averageChainLength = mapStats.pairs / mapStats.chains;
	
	return mapStats;
}

static size_t FindChains(const HashMap* _map)
{

	size_t i, numOfChains = 0;
	ListItr begin; 
	ListItr end;
	
	for(i=0; i < _map->m_hashSize; ++i)
	{
		begin = ListItr_Begin(_map->m_bucket[i]);
		end = ListItr_End(_map->m_bucket[i]);
		if(begin != end)
		{
			++numOfChains;
		} 
	
	}
	return numOfChains;
}

static size_t FindLongestChain(const HashMap* _map)
{

	size_t i, longestChain = 0;
	size_t chainlength =0;
	ListItr begin; 
	ListItr end;
	
	for(i=0; i < _map->m_hashSize; ++i)
	{
		begin = ListItr_Begin(_map->m_bucket[i]);
		end = ListItr_End(_map->m_bucket[i]);
		while(begin != end)
		{
			++chainlength;
			begin = ListItr_Next(begin);
		}
		if(chainlength > longestChain)
		{
			longestChain = chainlength;
		}
		chainlength = 0;
	}
	return longestChain;
}


