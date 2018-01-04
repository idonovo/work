
#include <stdlib.h>

#include "../../inc/Heap.h"
#include "../../inc/genVec.h"

#define MAGIC 7377175

#define PARENT(i) ((i)+1) 
#define NEXTPARENT(i) ((((i)-1)/2)+1) 
#define LEFT_CH(i) ((2*(i))+2) 
#define RIGHT_CH(i) ((2*(i))+3)  
#define IS_A_HEAP(h) ((h) && (h)->m_magic == MAGIC) 

struct Heap
{
	Vector* m_vec;
	int m_heapSize;
	int m_magic;
	LessThanComparator _less;
};

/***********************************************************/
/* static function to perform swap if nesscary while heapefy or bubbleup*/
static void Swap(Heap* _heap, size_t _firstIndex, size_t _lastIndex);
/* static rec to perform heapfy to an object in a heap */
static void Heapefy(Heap* _heap, size_t _parent, LessThanComparator _pfLess);
/* static rec. function to bubbleup the last elemant in a ap vector */
static void BubbleUp(Heap* _heap, size_t _index, LessThanComparator _less);

static Heap* CreateHeap(Vector* _vector,  LessThanComparator _pfLess);
/*************************************************************/
Heap* HeapBuild(Vector* _vector, LessThanComparator _pfLess){
	
	int i;
	Heap* newHeap;
	
	if(NULL == _vector || NULL == _pfLess)
	{
		return NULL;
	}
	
	newHeap = CreateHeap(_vector, _pfLess);
	if(!newHeap)
	{
		return NULL;
	}
/* a loop to perform heapefy on all the fathers in the heap*/	
	
	for(i = (newHeap->m_heapSize/2)-1; i >= 0; --i)
	{	
		Heapefy(newHeap, i, _pfLess);
	}
	return newHeap;
}

/****************************************************************/
Vector* HeapDestroy(Heap** _heap)
{

	Vector* vectorToReturn;
	
	if(!IS_A_HEAP(*_heap))
	{
		return NULL;
	} 
	
	vectorToReturn = (*_heap)->m_vec;
	(*_heap)->m_magic = 0;
	free(*_heap);
	*_heap = NULL;
		
	return vectorToReturn;
}

/****************************************************************/
Heap_Result HeapInsert(Heap* _heap, void* _element){

	if(!IS_A_HEAP(_heap))
	{
		return HEAP_NOT_INITIALIZED;
	} 
	
	if(NULL == _element)
	{
		return HEAP_INV_ARG;
	}

	if(VectorAppend(_heap->m_vec, _element) == ERR_REALLOCATION_FAILED)
	{
		return	HEAP_REALLOCATION_FAILED;
	}
	_heap->m_heapSize = VectorSize(_heap->m_vec);
	
/* Bubbleup the new elemant to e right position*/
	BubbleUp(_heap, --_heap->m_heapSize, _heap->_less);
	
	return HEAP_SUCCESS;
	
}

/****************************************************************/
const void* HeapPeek(const Heap* _heap){
	
	void* value;
	
	if(!IS_A_HEAP(_heap))
	{
		return NULL;
	}
	VectorGet(_heap->m_vec, 1, &value); 
	
	return value;
}

/***************************************************************/
void* HeapExtract(Heap* _heap){
	
	void* maxVal;
	void* minVal;
	if(NULL == _heap)
	{
		return NULL;
	} 
/* geting the max elemant in the heap. delete the last elemant and setting it in the head of the heap */	
	VectorGet(_heap->m_vec, 1, &maxVal);
	VectorRemove(_heap->m_vec, &minVal);
	VectorSet(_heap->m_vec, 1, minVal);
	_heap->m_heapSize = VectorSize(_heap->m_vec);
/* heapefy the first elemant */
	Heapefy( _heap, 0, _heap->_less);
	
	return maxVal;
	
}

size_t HeapSize(const Heap* _heap){

	return !IS_A_HEAP(_heap) ? 0 : _heap->m_heapSize; 

}


size_t HeapForEach(const Heap* _heap, ActionFunction _act, void* _context){
	
	size_t i;
	void* curVal;
	
	if(!IS_A_HEAP(_heap) || NULL ==_act)
	{
		return 0;
	}
	
	for(i = 1; i <= _heap->m_heapSize; ++i)
    {
        VectorGet(_heap->m_vec, i, &curVal);	
        
        if(_act(curVal, _context) == 0)
        {
            break;	
        }
    }
    return i;
	
}

void HeapSort(Vector* _vec, LessThanComparator _pfLess){
	
	Heap* sortHeap;

	if(NULL ==_pfLess || NULL == _vec)
	{
		return;
	} 
	
	sortHeap = CreateHeap(_vec, _pfLess);
	
	if(!sortHeap)
	{
		return;
	}
	
	while(!sortHeap->m_heapSize)
	{
		Swap(sortHeap, 1, sortHeap->m_heapSize);
		--sortHeap->m_heapSize;	
		Heapefy(sortHeap, 1, _pfLess);
		
	}
	return;
}

/**************************************************************************************/
static void Heapefy(Heap* _heap, size_t _parent, LessThanComparator _pfLess){
    
    size_t index;
	void* parentVal;
	void* leftVal;
	void* rightVal;
	
	if(RIGHT_CH(_parent) > _heap->m_heapSize)
	{
	    return;
	}
	
	VectorGet(_heap->m_vec, PARENT(_parent), &parentVal);	
	VectorGet(_heap->m_vec, LEFT_CH(_parent), &leftVal);
	VectorGet(_heap->m_vec, RIGHT_CH(_parent), &rightVal);
	/* if 0 parent is bigger. if 1 right ot left is bigger */
	if(_pfLess(parentVal, leftVal))
	{
        index = LEFT_CH(_parent);
        Swap(_heap, index, PARENT(_parent));
        Heapefy( _heap, index-1, _pfLess);
        VectorGet(_heap->m_vec, PARENT(_parent), &parentVal);
	}
	
	if( _pfLess(parentVal, rightVal))
	{
		index = RIGHT_CH(_parent);
		Swap(_heap, index, PARENT(_parent));
		Heapefy( _heap, index-1, _pfLess);	
	}
}

static void Swap(Heap* _heap, size_t _firstIndex, size_t _lastIndex){
	
	void* firstTemp;
	void* secondTemp;
	
	VectorGet(_heap->m_vec, _firstIndex, &firstTemp);
	VectorGet(_heap->m_vec, _lastIndex, &secondTemp);
	VectorSet(_heap->m_vec, _lastIndex, firstTemp);	
	VectorSet(_heap->m_vec, _firstIndex, secondTemp);
	return;
}
/**********************************************************************************/
static void BubbleUp(Heap* _heap, size_t _index, LessThanComparator _pfLess){

	void* parentVal;
	void* chVal;
	
	if(!_index)
	{
		return;
	}
	
	VectorGet(_heap->m_vec, PARENT(_index), &chVal);
	VectorGet(_heap->m_vec, NEXTPARENT(_index), &parentVal);
	
	if(_pfLess(parentVal, chVal))
	{
		Swap(_heap, PARENT(_index), NEXTPARENT(_index));
		BubbleUp(_heap, NEXTPARENT(_index)-1, _pfLess);
	}
	
	return;			
}

static Heap* CreateHeap(Vector* _vector, LessThanComparator _pfLess){
	
	Heap* newHeap =	malloc(sizeof(Heap));
	
	if (NULL == newHeap)
	{
		return NULL;
	}
	
	newHeap->m_vec = _vector;
	newHeap->m_heapSize = VectorSize(newHeap->m_vec);
	newHeap->m_magic = MAGIC;
	newHeap->_less = _pfLess;
	return newHeap;
}
