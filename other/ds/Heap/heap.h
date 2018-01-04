
#ifndef __MYHEAP__
#define __MYHEAP__

#include "vector.h" 
#include "ADTDefs.h"

typedef struct Heap Heap;

/*Desc.: Function to build a heap from exsisting vector. Tthe function create a heap struct and heapefy the vector.
Input: Vector struct.
Output: pointer to the new heap.
Error: NULL pointer if allocation failed.*/
Heap* HeapBuild(Vector* _vec);

/*Desc.: Function to destroy a heap struct without damaging the vector.
Input: Pointer to the heap struct. The function check a magin number inside the heap to prevent doubledestroy.
Output: _
Error: -.*/
void HeapDestroy(Heap* _heap);

/*Desc.: Function to insert a new object to the heap by placing it in the end pf the vector and bubble it up to the right place.
Input: Pointer to the heap and a data integerto insert.
Output: ADTErr ERR_OK.
Error: ADTErr errors if heap is NULL.*/
ADTErr HeapInsert(Heap* _heap, int _data);

/*Desc.: Function to to get the max elemant in the heap.
Input: Pointer to the heap and and adress to put in it the max elemant.
Output: ADTErr ERR_OK.
Error: ADTErr errors if heap or adress are NULL.*/
ADTErr HeapMax(Heap* _heap, int* _data);

/*Desc.: Function to extract the max elemant from the heap. Thefunction put the value of te max elemant on an address, andthen put the min. elemant in the head of the heap and heapefy it.
Input: Pointer to the heap and and adress to put in it the max elemant.
Output: ADTErr ERR_OK.
Error: ADTErr errors if heap or adress are NULL.*/
ADTErr HeapExtractMax(Heap* _heap, int* _data);

/*Desc.: Function to get the number of items in the heap.
Input: Pointer to the heap.
Output: Size_t value.
Error: returns 0 if heap is NULL.*/
size_t HeapItemsNum(Heap* _heap);

void HeapPrint(Heap* _heap);

#endif  /*__MYHEAP__ */
