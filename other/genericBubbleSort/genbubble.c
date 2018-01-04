
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "genbubble.h"

static void GenSwap(void* _left,  void* _right, void* _temp, size_t _size){

	memcpy(_temp, _left, _size);
	memcpy(_left, _right, _size);
	memcpy(_right, _temp, _size);
	return;
}

static ADTErr CheckParameters(void* _data, size_t _size, HowToSort _howTosort){

    ADTErr flag =0;
    if(NULL ==_data)
    {
	
		flag = ERR_NOT_INITIALIZED;
	}
	
	if(NULL ==_howTosort)
	{
	
		flag = ERR_NOT_INITIALIZED;
	}
	
	if(_size < 1){
	
		flag = ERR_INVALID_SIZE;
	}
    return flag;
    
}


ADTErr GenericBubble(void* _data, size_t _n, size_t _size, HowToSort _howTosort){

	size_t outIndex, innerIndex, flag, constSize;
	ADTErr parFlag;
	void* temp;
	void* curItem;-
	void* nextItem;
	
	parFlag = CheckParameters(_data, _size, _howTosort);
	
	if(parFlag != 0){
	    return parFlag;
	}
	
    if(_n < 2){
	
		return ERR_OK;
	}
	
	temp = malloc(sizeof(_size+_size));
	if(NULL == temp)
	{
		return  ERR_ALLOCATION_FAILED;
	}
	
	constSize = _n;
	
	for(outIndex = 0; outIndex < _n; outIndex++){
	
		flag =0;
		
		for(innerIndex = 0; innerIndex < constSize-1; innerIndex++)
		{
			curItem = (void*)((char*)_data + (innerIndex*_size));
			nextItem = (void*)((char*)_data + (innerIndex*_size)+_size);
			
			if(_howTosort(curItem, nextItem))
			{
				GenSwap(curItem, nextItem, temp, _size);
				++flag;
			}	
		}
		if(flag == 0){
			break;
		}
		--_n;
	}
	
	free(temp); 
	return ERR_OK;
}


