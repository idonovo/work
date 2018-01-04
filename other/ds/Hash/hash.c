#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MAGIC 7377175

typedef size_t Key;

struct Hash
{
    int* m_data;
    size_t m__capacity;
    size_t m_actualSize;
    size_t m_maxCollisions;
    size_t m_numberOfInsertions;
    size_t m_totalCollisions;
    size_t magic;
};

/******************************************************************/
static size_t HashFunc(Key key){
		
	size_t hashIndex = key;	
	
	return hashIndex;
} 

static int IsPrime(int _number){
	
	int i;
	for(i=2; i<sqrt(_number);i++)
	{
		if(_number%i == 0)
		{
		return 0;
		}
	}
	return 1;
}

static int IsFound(const Hash* _hash, int _data, int* emptyslot){
	
	size_t size = _hash->m_hashSize;
	size_t curIndex = HashFunc(_data)%_hash->m_hashSize;
	size_t maxOffset = _hash->m_maxCollisions;
	int i, flag = 0;
	*emptyslot = -1;
	
	for(i = curIndex; i <= curIndex+ maxOffset; i++)
	{
		if((_hash->m_data[i%size] == -1) && (*emptyslot == -1)) /*point to the first deleted place */
		{
			*emptyslot = (i%size);
		}
		
		if(_hash->m_data[i%size] == 0) 
		{
			*emptyslot = (i%size);
			break;
		}
		if(_hash->m_data[i%size] == _data)
		{
			flag++;
			break;
		}
	}
	return flag;
}

static void InsertEmptySlot(Hash* _hash, int _data){
	
	size_t size = _hash->m_hashSize;
	size_t curIndex =  HashFunc(_data)%_hash->m_hashSize;
	size_t maxOffset = _hash->m_maxCollisions;
	int i, jumpNum = 0;

	for(i = curIndex + maxOffset; i < size; i++)
	{
		if(_hash->m_data[i%size] == 0 || _hash->m_data[i%size] == -1)
		{
			 break;
		}
		jumpNum++;
	}
	
	_hash->m_data[i] = _data;
	++_hash-> m_numberOfInsertions;
	++_hash-> m_totalCollisions;
	if(jumpNum > maxOffset)
	{
		_hash->m_maxCollisions = jumpNum;
	}
	return;
}

/********************************************/
Hash* HashCreate(const size_t _size){
	
	Hash* newHash;
	size_t actualsize = _size;
	
	if(_size > 10)
	{
		return NULL;
	} 
	 
	newHash = malloc(sizeof(Hash));
	if(NULL == newHash)
	{
		return NULL;
	}
	
	actualsize *= 1.3;
		
	while(1)
	{
		if(IsPrime(actualsize))
		{
			break;
		}
		++actualsize;	
	}
	
	newHash->m_data = calloc(actualsize, sizeof(int));
	if(NULL == newHash->m_data)
	{
		return NULL;
	}
	
	newHash->m_originalSize = _size;
	newHash->m_hashSize = actualsize;
	newHash->m_maxCollisions = 0;
	newHash-> m_numberOfInsertions = 0;
	newHash->m_totalCollisions = 0;
	newHash->magic = MAGIC;
	 
	return newHash;
	
}

void HashDestroy(Hash* _hash){
	
	if(NULL == _hash)
	{
		return;
	}
	if(_hash->magic == MAGIC)
	{
		free(_hash->m_data);
		_hash->magic = 0;
		free(_hash);
	}
	return;
}

ADTErr HashInsert(Hash* _hash, int _data)
{
	int emptySlot;
	size_t size;
	
	if(NULL == _hash)
	{
		return ERR_NOT_INITIALIZED;
	}
    size = _hash->m_hashSize;
    
	if(_hash -> m_numberOfInsertions == _hash-> m_hashSize)
	{
		return ERR_OVERFLOW;
	}
	
	if(_data < 0)
	{
		return ERR_INVALID_NUM;
	}
	
	if(IsFound(_hash, _data, &emptySlot))
	{
		return ERR_INVALID_NUM;
	}
	
	if(emptySlot =! -1) 
	{
		if(emptySlot != _hash->m_data[ HashFunc(_data)%size])
		{
			_hash->m_data[emptySlot] = _data;
			++_hash-> m_numberOfInsertions;
			++_hash-> m_totalCollisions;
		}
		else
		{
			_hash->m_data[HashFunc(_data)%size] = _data;
			++_hash-> m_numberOfInsertions;
		}
		return ERR_OK;
	}
	else
	{
	InsertEmptySlot(_hash, _data);
	return ERR_OK;
	}
}	
	
ADTErr HashRemove(Hash* _hash, int _data){
	
	int i, emptyslot;
	size_t size = _hash->m_hashSize;
	size_t curIndex =  HashFunc(_data)%_hash->m_hashSize;
	size_t maxOffset = _hash->m_maxCollisions;
	
	if(NULL == _hash)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(0 == _hash->m_numberOfInsertions)
	{
		return ERR_UNDERFLOW;
	}
	if(IsFound(_hash, _data, &emptyslot))
	{		
		for(i = curIndex; i < (maxOffset + curIndex); i++)
		{
			if(_hash->m_data[i%size] == _data)
			{
				_hash->m_data[i%size] = -1;
				--_hash-> m_numberOfInsertions;
				return ERR_OK;
			}
		}
	}
	else
	{
	    return ERR_INVALID_NUM;
	}
}

int HashIsFound(const Hash* _hash, int _data){
	
	int emptyslot;
	
	if(NULL == _hash)
	{
		return 0;
	}
	
   	return IsFound(_hash, _data, &emptyslot);

}

size_t HashNumOfItems(const Hash* _hash){

	if(NULL == _hash)
	{
		return 0;
	}
	return _hash->m_numberOfInsertions;

}
size_t HashCapacity(const Hash* _hash){

	if(NULL == _hash)
	{
		return 0;
	}
	return _hash->m_originalSize;

}

double HashAverageCollisions(const Hash* _hash){

	double average;
	
	if(NULL == _hash)
	{
		return 0;
	}
	
	average = _hash->m_totalCollisions / _hash->m_numberOfInsertions;
    
    return average; 
	
}

size_t HashMaxCollisions(const Hash* _hash){

	if(NULL == _hash)
	{
		return 0;
	}
	
	return _hash->m_maxCollisions;
}

 void HashPrint(const Hash* _hash){
 
 	size_t i;
 	if(NULL != _hash)
	{	
		for(i=0; i< _hash->m_hashSize; i++){
			printf("[%d] %3d", i,  _hash->m_data[HashFunc(i)]);
		}
		printf("\n"); 	
	}
 	return;
}

		

