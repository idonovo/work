#ifndef __MYSORTS__
#define __MYSORTS__

#include <stddef.h>
#include "enum.h"
#include "vector.h"
#include "stack.h"

/* pointers type of functions which decides the direction of Insertin sort */
typedef int (*Switch)(int, int);

/* pointers type of sort functions  */
typedef ADTErr (*SortFunc)(Vector* _vector);

/* pointers type of functions which returns a value by key */
typedef int (*ValueByKey)(void* key, int value);

/*Desc.: function to perform bubble sort on a vector. 
Input: pointer to a vector.
Output: ERR_OK.
Error: ERR_NOT_INITIALIZED if vector is NULL.*/
ADTErr BubbleSort(Vector* _vector);

/*Desc.: function to perform shake sort on a vector. 
Input: pointer to a vector.
Output: ERR_OK.
Error: ERR_NOT_INITIALIZED if vector is NULL.*/
ADTErr ShakeSort(Vector* _vector);

/*Desc.: function to perform recursive quick sort on a vector. 
Input: pointer to a vector.
Output: ERR_OK.
Error: ERR_NOT_INITIALIZED if vector is NULL.*/
ADTErr QuickRec(Vector* _vector);

/*Desc.: function to perform iterative quick sort on a vector. 
Input: pointer to a vector.
Output: ERR_OK.
Error: ERR_NOT_INITIALIZED if vector is NULL.*/
ADTErr QuickSortIter(Vector* _vector);

/*Desc.: function to perform insertion sort on a vector. 
Input: pointer to a vector and to a function.
Output: ERR_OK.
Error: ERR_NOT_INITIALIZED if vector is NULL.*/
ADTErr InsertionSort(Vector* _vector, Switch _howToSwap);

/*Desc.: function to perform shell sort on a vector. 
Input: pointer to a vector and to a function.
Output: ERR_OK.
Error: ERR_NOT_INITIALIZED if vector is NULL.*/
ADTErr ShellSort(Vector* _vector);

/*Desc.: function to perform selection sort on a vector. 
Input: pointer to a vector.
Output: ERR_OK.
Error: ERR_NOT_INITIALIZED if vector is NULL.*/
ADTErr SelectionSort(Vector* _vector);

/*Desc.: function to perform rec. merge sort on a vector. 
Input: pointer to a vector.
Output: ERR_OK.
Error: ERR_NOT_INITIALIZED if vector is NULL.*/
ADTErr MergeSortRec(Vector* _vector);

/*Desc.: function to perform itterative merge sort on a vector. 
Input: pointer to a vector.
Output: ERR_OK.
Error: ERR_NOT_INITIALIZED if vector is NULL.*/
ADTErr MergeSortItter(Vector* _vector);

/*Desc.: function to perform counting sort on a vector. 
Input: pointer to a vector.
Output: ERR_OK.
Error: ERR_NOT_INITIALIZED if vector is NULL.*/
ADTErr CountingSort(Vector* _vector, ValueByKey _valueByKey,  int _key, int _maxValue);

/*Desc.: function to perform radix sort on a vector. 
Input: pointer to a vector.
Output: ERR_OK.
Error: ERR_NOT_INITIALIZED if vector is NULL.*/
ADTErr RadixSort(Vector* _vector, int _nDigits);

#endif  /*__MYSORTS__ */
