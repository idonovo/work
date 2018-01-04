
#ifndef __GENBUBBLE_H__
#define __GENBUBBLE_H__

#include "ADTDefs.h"
#include <stddef.h>

/* bolean functions type to decide if swap between to objects is needed. the functions recives two void pointers and retruns 1 to swap or 0 if not*/ 
typedef int (*HowToSort)(const void*, const void*);

/*Desc.: Generic function to sort objects using bubblesort algorithem.
Input: void pointer for data to be sorted. size_t number of items. size_t size in bytes of each object and a pointer to to How to sort function.
Output: ADTErr ERR_OK if the sort succeded or if noe is < 2;
Error: 	ERR_NOT_INITIALIZED if the data or the function pointer are NULL. ERR_ALLOCATION_FAILED if allocation of a temp object waf failed. ERR_INVALID_SIZE if the size of objects is 0. */
ADTErr GenericBubble(void* _data, size_t _n, size_t _size, int (*HowToSort)(const void*, const void*));

#endif  /*___GENBUBBLE_H__ */
