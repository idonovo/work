
#include "sorts.h"

#include <stdio.h>
#include <stdlib.h>


static void RecQuickSort(Vector* _vector, unsigned int _beginIndex, unsigned int _endIndex);

static unsigned int Partition(Vector* _vector,  unsigned _beginIndex, unsigned int _endIndex);

static void Replace(Vector* _vector, unsigned int _index, unsigned int* _flag);

int SmallToBigSwitch(int _curNum, int _beforeNum);

int BigToSmallSwitch(int _curNum, int _beforeNum);

static void InsertionSortForShell(Vector* _vector, size_t _size, size_t _gap);

static void RecMergeSort(Vector* _vector, int* _array, size_t _begin, size_t _end);

static void Merge(Vector* _vector, int* _array, size_t _begin, size_t _middle, size_t _end);

static void FillRangeArray(int* _initialArray, int* _rangArray, size_t _size);

static void SumRangeArray(int* _rangArray, int _maxValue);

/*static void FillTempArray(int* _initialArray, int* _sortedArray , int* _rangArray, size_t _size);*/

/*static void FillRangeArrayFromArray(int* _array, int* _rangArray, size_t _size);*/

/**********************************************************************************************/
ADTErr BubbleSort(Vector* _vector){
    
    unsigned int outIndex, innerIndex, flag, constSize;
    size_t size; 
    
    if(NULL == _vector)
    {
        return  ERR_NOT_INITIALIZED;
    }
    
	VectorItemsNum(_vector, &size);
	
	if (size == 0 || size == 1){
	    return ERR_OK;
	}
	constSize = size;
	
	for(outIndex = 0; outIndex < constSize; outIndex++){
		flag =0;
		for(innerIndex = 0; innerIndex < size-1; innerIndex++)
		{
			Replace(_vector,innerIndex, &flag);
		}
		if(flag == 0){
			break;
		}
		--size;
	}
	return ERR_OK;
}


ADTErr ShakeSort(Vector* _vector){

	unsigned int i,curIndex, flag, constSize, start =0;
	size_t size; 
	
	if(NULL == _vector)
    {
        return  ERR_NOT_INITIALIZED;
    }
	
	VectorItemsNum(_vector, &size);
	
	if (size == 0 || size == 1){
	    return ERR_OK;
	}
	
	constSize = size;
	
	for(i = 0; (constSize)/2 ; i++)
	{	
		flag =0;
		
		for(curIndex = start; curIndex < size-1; curIndex++)
		{
			Replace(_vector, curIndex, &flag);	
		}
		if(flag == 0)
		{
			break;
		}	
		flag =0;
		--size;
		
		for(curIndex = size-1; curIndex > start ; curIndex--)
		{
			Replace(_vector, curIndex, &flag);
		}
		if(flag == 0)
		{
			break;
		}	
		++start;
	}
	return ERR_OK;
}

ADTErr QuickRec(Vector* _vector){
    
    unsigned int begin = 0;
	size_t end; 
	
    if(NULL == _vector)
    {
        return  ERR_NOT_INITIALIZED;
    }
	
	VectorItemsNum(_vector, &end);
	
	if (end < 2){
	    return ERR_OK;
	}
	
	RecQuickSort(_vector, begin, end-1);
	
	return ERR_OK;
}

ADTErr QuickSortIter(Vector* _vector){
    
    int endIndex;
    size_t size; 
    int beginIndex;
    int pivot;
    Stack* sortStack;
    
    if(NULL == _vector)
    {
        return  ERR_NOT_INITIALIZED;
    }
    
    sortStack = StackCreate(5000, 100);
    VectorItemsNum(_vector, &size);
    
    if (size < 2)
    {
	    return ERR_OK;
	}
    endIndex = size-1;
    pivot = Partition(_vector, beginIndex, endIndex);
    
    StackPush(sortStack, 0);
    StackPush(sortStack,pivot-1);
    StackPush(sortStack, pivot+1);
    StackPush(sortStack, endIndex);
    
    while(StackIsEmpty(sortStack) != 1)
    {
        StackPop(sortStack, &endIndex); 
        StackPop(sortStack, &beginIndex);          
        
        pivot = Partition(_vector, beginIndex, endIndex);

        if((pivot-1) > beginIndex)
        {
             StackPush(sortStack, beginIndex);
             StackPush(sortStack, pivot-1);
        }
        
        if((pivot+1) < endIndex)
        {
             StackPush(sortStack, pivot+1);
             StackPush(sortStack, endIndex);
        }  	
        
    }
    
    return ERR_OK;
}

ADTErr InsertionSort(Vector* _vector, Switch _howToSwap){
	
	size_t i, curIndex;
	int curNum, beforeNum, isSwap;
	size_t size; 
	if(NULL == _vector)
    {
        return  ERR_NOT_INITIALIZED;
    }
    
    VectorItemsNum(_vector, &size);
    
    if (size < 2)
    {
	    return ERR_OK;
	}

	for(i = 1; i < size; i++){
		
		curIndex = i;
	
		while(curIndex > 0){
		
			VectorGet(_vector, curIndex, &curNum);
   	 		VectorGet(_vector, curIndex-1, &beforeNum);
   	 		
			isSwap = (*_howToSwap)(curNum, beforeNum);
			
			if(isSwap){
			
				VectorSet(_vector, curIndex, beforeNum);
				VectorSet(_vector, curIndex-1, curNum);
				curIndex--;
			}
			else
			{
				break;
			}
			
		}
	}
	return ERR_OK;
}

ADTErr SelectionSort(Vector* _vector){

	size_t i, compareIndex, tempIndex;
	int curNum, tempNum, compareNum;
	size_t size;
	 
	if(NULL == _vector)
    {
        return  ERR_NOT_INITIALIZED;
    }
    
    VectorItemsNum(_vector, &size);
    
    if (size < 2)
    {
	    return ERR_OK;
	}
	
	for(i = 0; i < size; i++)
	{
		VectorGet(_vector, i, &curNum);
		tempNum = curNum;
		tempIndex = i;
		
		for(compareIndex = i+1; compareIndex < size; compareIndex++)
		{
			VectorGet(_vector, compareIndex, &compareNum);
			if(tempNum > compareNum)
			{
				tempNum = compareNum;
				tempIndex = compareIndex;
			}
		} 
		VectorSet(_vector, i, tempNum);	
		VectorSet(_vector, tempIndex, curNum);	
	}
	
	return ERR_OK;
}


ADTErr ShellSort(Vector* _vector){

	size_t gap;
	size_t size; 
	
	if(NULL == _vector)
    {
        return  ERR_NOT_INITIALIZED;
    }
    
    VectorItemsNum(_vector, &size);
    
    if (size < 2)
    {
	    return ERR_OK;
	}
	
	for(gap = size/2; gap > 0; gap = gap/2)
	{
		InsertionSortForShell(_vector, size, gap);
	}
	
	return ERR_OK;
}


ADTErr MergeSortItter(Vector* _vector){

    size_t left, right, size, middle, mergingSize;
    int* array;
    
    if(NULL == _vector)
    {
        return  ERR_NOT_INITIALIZED;
    }
	
	VectorItemsNum(_vector, &size);
	
	if (size < 2){
	    return ERR_OK;
	}
    
	array = malloc(size*sizeof(int));
	
	if(NULL == array)
	{
		 ERR_NOT_INITIALIZED;
	} 
	
    for(mergingSize = 1; mergingSize < size; mergingSize= mergingSize*2)
    {
       for(left = 0; left <= size-1; left = left+ (mergingSize*2)){
       		
       		right = left+ (mergingSize*2)-1;
       		if(size - left < mergingSize*2)
       		{
       			right = size-1;
       			
       		} 
       		middle = left+mergingSize;			
            Merge(_vector, array, left, middle, right);
       }     
    } 
	free(array);
    return ERR_OK;

}

ADTErr MergeSortRec(Vector* _vector){

	size_t left = 0;
	size_t right;
	int* array;
	
    if(NULL == _vector)
    {
        return  ERR_NOT_INITIALIZED;
    }
	
	VectorItemsNum(_vector, &right);
	
	if (right < 2){
	    return ERR_OK;
	}
	
	array = malloc(right*sizeof(int));
	
	if(NULL != array)
	{
		RecMergeSort(_vector, array, left, right-1);
	} 
	
	free(array);
	return ERR_OK;

}

ADTErr CountingSort(Vector* _vector, ValueByKey _valueByKey, int _key, int _maxValue){

	size_t size, x;
	int* rangeArray;
	int* sortedArray;
	int* initialArray;
	int curNum, i, index;	
	
	if (_maxValue < 1){
	    return ERR_OK;
	}
	
    if(NULL == _vector)
    {
        return  ERR_NOT_INITIALIZED;
    }
	
	VectorItemsNum(_vector, &size);
	
	if (size < 2){
	    return ERR_OK;
	}
	
	rangeArray = calloc(_maxValue+1, sizeof(int));
	
	if(NULL ==  rangeArray)
    {
        return  ERR_NOT_INITIALIZED;
    }
    
    sortedArray = calloc(size+10, sizeof(int));
	
	if(NULL ==  sortedArray)
    {
        return  ERR_NOT_INITIALIZED;
    }
    
   	initialArray = calloc(size, sizeof(int));
	
	if(NULL ==  sortedArray)
    {
        return  ERR_NOT_INITIALIZED;
    }
    
    if (NULL != _valueByKey)
    {
    	for(i = 0; i < size; ++i)
		{
			VectorGet(_vector, i, &curNum);
			initialArray[i] = _valueByKey((void*)_key, curNum);
		}	
    }
    else
    {
    	for(i = 0; i < size; ++i)
		{
			VectorGet(_vector, i, &curNum);
			initialArray[i] = curNum;
    	} 
    }
    
	FillRangeArray(initialArray, rangeArray, size);
	
	SumRangeArray(rangeArray, _maxValue+1);
	
	for(i = size-1; i >= 0; --i)
	{
		VectorGet(_vector, i, &curNum);
		index = rangeArray[initialArray[i]];
		sortedArray[index] = curNum;
		--rangeArray[initialArray[i]];					
	}
		
	for(x = 1; x <= size; ++x)
	{
		VectorSet(_vector, x-1, sortedArray[x]);	
	}
	/*free(initialArray);*/
	free(rangeArray);
	/*free(sortedArray);*/
	
	return ERR_OK;
	
}

static void FillRangeArray(int* _initialArray, int* _rangArray, size_t _size){
	
	size_t i;
	int curNum;
	for(i=0; i<_size; i++)
	{
		curNum = _initialArray[i];
		++_rangArray[curNum];
	}
	
	return;
}


static void SumRangeArray(int* _rangArray, int _maxValue){
	
	size_t i;
	int curNum;
	for(i = 1; i <= _maxValue; i++)
	{

		_rangArray[i] = _rangArray[i] + _rangArray[i-1];
	}
	
	return;
}

static int RadixKey(void* _key, int _value){
	
	return (_value/(int)_key)%10;
}

ADTErr RadixSort(Vector* _vector, int _nDigits){

	size_t size, i, key;
	
	if (_nDigits < 1){
	    return ERR_OK;
	}
	
    if(NULL == _vector)
    {
        return  ERR_NOT_INITIALIZED;
    }
	
	VectorItemsNum(_vector, &size);
	
	if (size < 2){
	    return ERR_OK;
	}
	
	key = 1;

	
	for(i = 0; i<_nDigits; i++)
	{
		CountingSort(_vector, RadixKey, key, 9);
		key *= 10;	
		
	}
	
	return ERR_OK;
}


static void RecMergeSort(Vector* _vector, int* _array, size_t _left, size_t _right){

	size_t middle;
	
	if(_left == _right){
	
		return;
	}
	
	middle = (_left + _right)/2;
	
	RecMergeSort(_vector, _array, _left, middle);

	RecMergeSort(_vector, _array, middle+1, _right); 
	
	Merge(_vector, _array, _left, middle+1, _right);
	 
}

static void Merge(Vector* _vector, int* _array, size_t _left, size_t _middle, size_t _right){
	
	size_t i, constLeft, middle, constMiddle;
	int leftVal, rightVal;
	i = _left;
	constLeft = _left;
	
	if(_middle > _right)
	{
	 _middle = _right;
	}
	constMiddle = _middle;

	VectorGet(_vector, _left, &leftVal);
	VectorGet(_vector,  _middle, &rightVal);
	
	while( constMiddle > _left && _right >= _middle){
		
		if(leftVal <= rightVal)
		{
			_array[i] = leftVal;
			VectorGet(_vector,  ++_left, &leftVal);
			++i;

		}
		else
		{
			_array[i] = rightVal;
			VectorGet(_vector,  ++_middle, &rightVal);
			++i;
		}	
	}
	
	while(constMiddle > _left)
	{
		_array[i] = leftVal;
		++_left;
		VectorGet(_vector, _left, &leftVal);
		++i;
	} 
	
	while(_right >= _middle)
	{
		_array[i] = rightVal;
		VectorGet(_vector,  ++_middle, &rightVal);
		++i;
	
	} 
	
	for(i = constLeft; i <= _right; i++)
	{
		VectorSet(_vector, i, _array[i]);
	}
	return; 
	  	
}

static void InsertionSortForShell(Vector* _vector, size_t _size, size_t _gap){
	
	size_t i, curIndex;
	int curNum, beforeNum;
    
		
	for(i = _gap ; i < _size; i = i + _gap){

		curIndex = i;

		while(curIndex > 0){
	
			VectorGet(_vector, curIndex, &curNum);
   	 		VectorGet(_vector, curIndex - _gap, &beforeNum);
   	 		
   	 		if(curNum < beforeNum)
   	 		{
   
				VectorSet(_vector, curIndex, beforeNum);
				VectorSet(_vector, curIndex-_gap, curNum);
				curIndex =  curIndex - _gap;
			}
			else
			{
				break;
			}	
		}
	
    }
	
	
	return; 
}

static void Replace(Vector* _vector, unsigned int _index, unsigned int* _flag){
		
    int curNum, nextNum;
    
    VectorGet(_vector, _index, &curNum);
    VectorGet(_vector, _index+1, &nextNum);

    if(curNum > nextNum)
    {
	    VectorSet(_vector, _index, nextNum);
	    VectorSet(_vector, _index+1, curNum);
	    *_flag = 1;
    }	

    return;
}

static unsigned int Partition(Vector* _vector,  unsigned int _beginIndex, unsigned int _endIndex){
    
    int last, start, pivot;
    size_t constIndex = _beginIndex;
    
	VectorGet(_vector, _beginIndex, &pivot);
	++_beginIndex;
	VectorGet(_vector, _endIndex, &last);
	VectorGet(_vector,  _beginIndex, &start);
	
    while(_beginIndex < _endIndex)
	{		
		
		while(pivot < last)
		{
			--_endIndex;
			VectorGet(_vector, _endIndex, &last);
		}
		
		while(pivot >= start && _beginIndex < _endIndex)
		{
			++ _beginIndex;
			VectorGet(_vector,  _beginIndex, &start);
		}	

		if(_beginIndex < _endIndex)
		{
			VectorSet(_vector,  _beginIndex, last);
			VectorSet(_vector, _endIndex, start);
			--_endIndex;
			++_beginIndex;
			VectorGet(_vector, _endIndex, &last);
	        VectorGet(_vector,  _beginIndex, &start);
		}	
	}
	if(last < pivot)
	{
	    VectorSet(_vector,  _endIndex, pivot);
	    VectorSet(_vector, constIndex, last);
	}
	

	return _endIndex;
	
}

static void RecQuickSort(Vector* _vector, unsigned int _beginIndex, unsigned int _endIndex){

	int pivot;
	
	if(_endIndex <= _beginIndex)
	{
	    return;
	}

	pivot = Partition(_vector, _beginIndex, _endIndex);
    
	RecQuickSort(_vector, _beginIndex, pivot -1);
	RecQuickSort(_vector,  pivot +1, _endIndex);	
}




int SmallToBigSwitch(int _curNum, int _beforeNum){

    if(_curNum < _beforeNum)
    {
		return 1;
    }	

    return 0;
}

int BigToSmallSwitch(int _curNum, int _beforeNum){
	
    if(_curNum > _beforeNum)
    {
		return 1;
    }	

    return 0;

}


	
	
	
	
	
	
	
	
