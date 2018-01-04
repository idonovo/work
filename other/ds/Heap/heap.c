#include <stdio.h>
#include <stdlib.h>

# include "heap.h"

#define MAGIC 7377175
 

struct Heap
{
	Vector* m_vec;
	int m_heapSize;
	int magic;
};

/******************************************************/
/* static function to perform swap if nesscary while heapefy or bubbleup*/
static void Swap(Heap* _heap, int _firstIndex, int _lastIndex){
	
	int temp1;
	int temp2;
	
	VectorGet(_heap->m_vec, _firstIndex, &temp1);
	VectorGet(_heap->m_vec, _lastIndex, &temp2);
	VectorSet(_heap->m_vec, _lastIndex, temp1);	
	VectorSet(_heap->m_vec, _firstIndex, temp2);
	return;
}
/* static rec to perform heapfy to an object in a heap */
static void Heapefy(Heap* _heap, int _curfather){
	
	int iLargest = _curfather;
	int father, left, right;
	
	if((2*_curfather)+1 > _heap->m_heapSize){
	    return;
	}
	
	VectorGet(_heap->m_vec, iLargest, &father);	
	VectorGet(_heap->m_vec, (2*_curfather)+1, &left);
	VectorGet(_heap->m_vec, (2*_curfather)+2, &right);

	if(left > father)
	{
		iLargest = (2*_curfather)+1;
	}
	if(right > father)
	{
		iLargest = (2*_curfather)+2;
	}
	
	if(iLargest !=_curfather){
		Swap(_heap, iLargest, _curfather);
		Heapefy( _heap, iLargest);		
	}
	else
	{
		return;
	}
}
/* static rec. function to bubbleup the last elemant in a ap vector */
static void BubbleUp(Heap* _heap, int _ilast){

	int largest = _ilast-1;
	int father, child;
	
	VectorGet(_heap->m_vec, largest, &child);
	VectorGet(_heap->m_vec, (largest-1)/2, &father);
	
	if(_ilast == 0){
		return;
	}
	if(father > child)
	{
		return;
	}
	
	if(child > father)
	{
		Swap(_heap, largest, (largest-1)/2);
		largest = (largest-1)/2;
		BubbleUp(_heap,largest);
	}			
}

/**********************************************/
Heap* HeapBuild(Vector* _vec){
	
	int curfather;
	Heap* newHeap = malloc(sizeof(Heap));
	if (NULL == newHeap){
		return NULL;
	}
	newHeap->m_vec = _vec;
	VectorItemsNum(newHeap->m_vec, &newHeap->m_heapSize);
	newHeap->magic = MAGIC;
/* a loop to perform heapefy on all the fathers in the heap*/	
	for(curfather = (newHeap->m_heapSize/2)-1; curfather >= 0; --curfather)
	{	
		Heapefy(newHeap, curfather);
	}
	return newHeap;
}

void HeapDestroy(Heap* _heap){
	
	if(_heap->magic == MAGIC){
		_heap->magic = 0;
		free(_heap);
	}
	return;
}

ADTErr HeapInsert(Heap* _heap, int _data){

	if(NULL ==_heap){
		return  ERR_NOT_INITIALIZED;
	}
/* insert the new data as the last elemant in the heap */ 
	VectorAdd(_heap->m_vec,  _data);
	
	VectorItemsNum(_heap->m_vec, &_heap->m_heapSize);

/* Bubbleup the new elemant to e right position*/
	BubbleUp(_heap, _heap->m_heapSize);
	
	return ERR_OK;
	
}
ADTErr HeapMax(Heap* _heap, int* _data){
	
	if(NULL == _heap){
		return ERR_NOT_INITIALIZED;
	} 
	if(NULL ==_data){
		return  ERR_ALLOCATION_FAILED;
	}
	VectorGet(_heap->m_vec, 0, _data);
	
	return ERR_OK;
}

ADTErr HeapExtractMax(Heap* _heap, int* _data){
	
	int firstindex;
	if(NULL == _heap){
		return ERR_NOT_INITIALIZED;
	} 
	if(NULL ==_data){
		return  ERR_ALLOCATION_FAILED;
	}

/* geting the max elemant in the heap. delete the last elemant and setting it in the head of the heap */	
	VectorGet(_heap->m_vec, 0, _data);
	VectorDelete(_heap->m_vec, &firstindex);
	VectorSet(_heap->m_vec, 0, firstindex);
/* heapefy the first elemant */
	Heapefy( _heap, 0);
	
	return  ERR_OK;
}
size_t HeapItemsNum(Heap* _heap){
	
	if(NULL == _heap){
		return 0;
	} 
	return _heap->m_heapSize;
}

void HeapPrint(Heap* _heap){
	
	if(NULL != _heap){
		VectorPrint(_heap->m_vec);
	} 
}

/*************************************************/








