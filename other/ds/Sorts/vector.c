#include <stdio.h>
#include <stdlib.h>

#include "vector.h"



struct Vector

{

    int*    m_items;

    size_t  m_originalSize;   /* original allocated space for items) */

    size_t  m_size;                 /* actual allocated space for items) */

    size_t  m_nItems;           /* actual number of items */

    size_t  m_blockSize;     /* the chunk size to be allocated when no space*/

};

/*********************************************/

Vector* VectorCreate(size_t _initialSize, size_t _extensionBblockSize){

/* creating a pointer to the struct and dynamic array using malloc */
 
	Vector* vector;
	vector= malloc(sizeof(Vector));
	vector->m_items=malloc(_initialSize*sizeof(int));
	
	if (vector == NULL){
		 return NULL;
	}
	
	if (vector->m_items == NULL){
		 return NULL;
	}
	/* initial the struct */
	vector->m_originalSize = _initialSize;
	vector->m_size = _initialSize;
	vector->m_nItems = 0;
	vector->m_blockSize = _extensionBblockSize;
	
	
	return vector;

}
/*********************************************/

void VectorDestroy(Vector* _vector){
	
	int i;
	
	if(_vector == NULL){
	
		printf("No Valid Vector");
	
	}

  /* free the array and then the struct */
	
	free(_vector->m_items);
	free(_vector);
	return;
	
}

/**********************************************/
ADTErr VectorAdd(Vector *_vector,  int  _item){

	int i ;
	int* temp;
	
	/* check if realloc is neaded */	
	if (_vector -> m_size == _vector->m_nItems){
		
		temp= realloc(_vector->m_items,(_vector->m_size + _vector-> m_blockSize)*sizeof(int));
			if (temp==NULL){
			
				return ERR_REALLOCATION_FAILED;
			}
	/* if succeed updating the struct members */
			else{
			_vector->m_items = temp;
			free(temp);
			_vector->m_size = _vector->m_size +_vector-> m_blockSize ;
        	}
		}
			

	/* adding the integer to the vector */	
	_vector->m_items[_vector->m_nItems]= _item;
	
	_vector->m_nItems++;
	
		return ERR_OK; 
}

/**********************************************/

ADTErr VectorDelete(Vector *_vector,  int* _item){
	
	int i;
	int* temp; 
	
	if(_vector == NULL){
	
		return ERR_NOT_INITIALIZED;
	
	}
	
	*_item = _vector->m_items[_vector->m_nItems-1];
	
	_vector->m_nItems--;


	/* checkinf if the array have space size of more than 2 chunks and realloc to decrease the array */ 	
	if (_vector->m_size >= _vector->m_nItems + (2 * _vector -> m_blockSize)){
	
		temp = realloc(_vector->m_items,(_vector->m_nItems + _vector-> m_blockSize)*sizeof(int));
		
				
			if (temp == NULL){
			
				return ERR_REALLOCATION_FAILED;
				
			}
		
		
		_vector->m_items = temp;
		
		_vector->m_size =- _vector-> m_blockSize;
	}
	
	return ERR_OK;

}

/**********************************************/

ADTErr VectorGet(Vector *_vector, size_t _index, int *_item){

	if(_vector == NULL){
	
		return ERR_NOT_INITIALIZED;
	
	}
	
	/* check if index is valid */
	if(_index >= _vector->m_nItems){
	
		return ERR_OVERFLOW;
	
	}
	
	if(_index < 0){
	
		return ERR_UNDERFLOW;
	
	}
	
	/* initial the _item with the relevant elemant in the array */
	
	*_item = _vector-> m_items[_index];
	
	return ERR_OK;

}

/**************************************************************/
ADTErr VectorSet(Vector *_vector, size_t _index, int _item){

	if(_vector == NULL){
	
		return ERR_NOT_INITIALIZED;
	
	}
	
	/* check if index is valid */
	if(_index >= _vector->m_nItems){
	
		return ERR_OVERFLOW;
	
	}
	
	if(_index < 0){
	
		return ERR_UNDERFLOW;
	
	}
	
	/* set the array[_index] with the new _item */
	_vector-> m_items[_index] = _item;
	
	return ERR_OK;	
	
}

/**************************************************************/
ADTErr VectorItemsNum(Vector *_vector, size_t*  _numOfItems){

	if(_vector == NULL){
	
		return ERR_NOT_INITIALIZED;
	
	}
	
	/* assigned the pointer with m_nItems */
	
	*_numOfItems = _vector->m_nItems;

	return ERR_OK;
}

/**************************************************************/

void VectorPrint(Vector *_vector){

	int i;
	if(_vector == NULL){
	
		printf("vector not valid");
	
	}

/* printing the array using for loop */

	for(i=0; i < _vector->m_nItems; i++){
	
		printf("[%d]:%d\t", i, _vector->m_items[i]); 
	}
	printf("\n");
	return;
}

