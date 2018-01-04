#include <stdio.h>
#include <stdlib.h>

#include "../../inc/genVec.h"

struct Vector
{
    void**  m_items;
    size_t  m_originalSize;  
    size_t  m_size;  
    size_t  m_nItems;       
    size_t  m_blockSize;   

};

/* bolean function to check if a _vector paramter is NULL */
static int IsNullVector(const Vector* _vector);
/* bolean function to check if a _vector need extand realloc. the function also execute the realloc accordingly */
static int IfExtand(Vector* _vector);
/* bolean function to check if a _vector need shrink realloc. the function also execute the realloc accordingly */
static int IfShrink(Vector* _vector);
/* bolean function to check if an index recivied from the user is he range of the _vector*/
static int IsValidIndex(const Vector* _vector, size_t _index);
/* bolean function to check if a _vector is full and with fixed sized (_blockSize == 0)*/
static int IsFixedFull(const Vector* _vector);

/*****************************************************************************/
Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize){

	Vector* vector;
	
	if (_initialCapacity == 0 && _blockSize == 0)
	{
		return NULL;
	}
	
	vector= malloc(sizeof(Vector));
	if (vector == NULL)
	{
		 return NULL;
	}
	
	vector->m_items=malloc(_initialCapacity*sizeof(void*));
	
	if (vector->m_items == NULL ){
		 return NULL;
	}
	
	vector->m_originalSize = _initialCapacity;
	vector->m_size = _initialCapacity;
	vector->m_nItems = 0;
	vector->m_blockSize = _blockSize;
	
	return vector;

}

void VectorDestroy(Vector** _vector, void (*_elementDestroy)(void* _item)){

	size_t i;
    if(IsNullVector(*_vector))
	{
		return;
	}
	
	if((*_vector)->m_items != NULL)
	{
		if(_elementDestroy != NULL && (*_vector)->m_nItems != 0)
		{
			for(i = 0; i < (*_vector)->m_nItems; ++i)
			{
				 _elementDestroy((*_vector)->m_items[i]);
			}	
		}
		free((*_vector)->m_items);	
	}
	
	free(*_vector);
	_vector = NULL;
	
	return;
}

ADTErr VectorAppend(Vector* _vector, void* _item){
    
    if(IsNullVector(_vector))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if (_item == NULL){
	
		return ERR_NOT_INITIALIZED;
	}
	
	if (IsFixedFull(_vector))
	{
		return ERR_OVERFLOW;
	}
	
	if(!IfExtand(_vector))
	{
		 return ERR_REALLOCATION_FAILED;
	}
			
	_vector->m_items[_vector->m_nItems] = _item;
	++_vector->m_nItems;
	
	return ERR_OK; 
}


ADTErr VectorRemove(Vector* _vector, void** _item){

	if(IsNullVector(_vector))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(_vector->m_nItems == 0)
	{
		return ERR_UNDERFLOW;
	}
	
	if( _item == NULL)
	{
		return ERR_NOT_INITIALIZED;	
	}
	
	if(!IfShrink(_vector))
	{
		return ERR_REALLOCATION_FAILED;
	}
		
	*_item = _vector->m_items[_vector->m_nItems-1];	
	--_vector->m_nItems;
	
	return ERR_OK;
}

ADTErr VectorGet(const Vector* _vector, size_t _index, void** _item){

	if(IsNullVector(_vector))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(!IsValidIndex(_vector, _index))
	{
	    return ERR_WRONG_INDEX;
	}
	
	if(_item == NULL)
	{
		return ERR_NOT_INITIALIZED;	
	}
	
	*_item =_vector-> m_items[_index-1];
	
	return ERR_OK;
}

ADTErr VectorSet(Vector* _vector, size_t _index, void*  _item){

	if(IsNullVector(_vector))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(!IsValidIndex(_vector, _index))
	{
	    return ERR_WRONG_INDEX;
	}
	
	if(_item == NULL)
	{
		return ERR_NOT_INITIALIZED;	
	}
	
	_vector-> m_items[_index-1] = _item;
	
	return ERR_OK;	
}


size_t VectorSize(const Vector* _vector){
    
    if(IsNullVector(_vector) || 0 == _vector->m_nItems)
	{
		return 0;
	}

	return _vector->m_nItems;

}

size_t VectorCapacity(const Vector* _vector){

	if(IsNullVector(_vector))
	{
		return 0;
	}

	return _vector->m_size;
	
}

size_t VectorForEach(const Vector* _vector, VectorElementAction _action, void* _context){
    size_t i;
    
    for(i = 0; i < _vector->m_nItems; ++i)
    {
        if(_action(_vector->m_items[i], _context) == 0)
        {
            break;	
        }
    }
    return i;
}

/****************************static functions************************************/

static int IsNullVector(const Vector* _vector){
    
    if(NULL ==_vector || NULL ==_vector->m_items)
    {
		return 1;
	}
	
    return 0;
}

static int IsValidIndex(const Vector* _vector, size_t _index){

    if(_index > _vector->m_nItems || _index == 0)
	{
		return 0;
	}
	return 1;
}

static int IsFixedFull(const Vector* _vector){

    if((_vector-> m_blockSize == 0) && (_vector -> m_size == _vector->m_nItems))
    {
        return 1;
    }
    return 0;
}

static int IfExtand(Vector* _vector){

	if(_vector->m_size == _vector->m_nItems){
		
		_vector->m_items = realloc(_vector->m_items,(_vector->m_size + _vector-> m_blockSize)*sizeof(void*));
		
		if (_vector->m_items==NULL)
		{
			return 0;
		}
		else
		{
			_vector->m_size = _vector->m_size +_vector-> m_blockSize ;
    	}
	}
	return 1;
}
	
static int IfShrink(Vector* _vector){

	if ((_vector->m_size >= _vector->m_nItems + _vector -> m_blockSize) & (_vector->m_size + _vector -> m_blockSize > _vector->m_originalSize))
	{
		_vector->m_items = realloc(_vector->m_items,(_vector->m_nItems + _vector-> m_blockSize)*sizeof(void*));
		
			if (_vector->m_items==NULL)
			{
				return 0;
			}
	_vector->m_size = _vector->m_size - _vector-> m_blockSize;
	}
	return 1;
}

/***********************************************************************/
