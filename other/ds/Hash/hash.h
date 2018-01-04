
#ifndef __MYHASH__
#define __MYHASH__

#include <stdlib.h>

#include "ADTDefs.h"

typedef struct Hash Hash;


/*Desc.: function to create a hash struct.
Input: size of the requested hash._
Output: pointer to the new hash.
Error: NULL pointer if allocation failed.*/
Hash* HashCreate(const size_t _size);

/*Desc.: function to destroy a hash.
Input:  pointer to the hash.
Output: _
Error:  _*/
void HashDestroy(Hash* hash);

/*Desc.: function to insert new elements into a hash using the hash key (data%size_of_thr_hash). 
Input: pointer to a hash and data to insert.
Output: ERR_OK.
Error: ERR_NOT_INITIALIZED if hash id NULL,ERR_OVERFLOW if the hash is full, ERR_INVALID_NUM if the number to insert below 1 or if the number already exist.*/
ADTErr HashInsert(Hash* _hash, int _data);

/*Desc.: function to remove elements from a hash and replace them with -1. 
Input: pointer to a hash and data to remove.
Output: ERR_OK.
Error: ERR_NOT_INITIALIZED if hash id NULL,ERR_UNDERFLOW if the hash is empty, ERR_INVALID_NUM if the number to insert not exist in the hash.*/
ADTErr HashRemove(Hash* _hash, int _data);

/*Desc.: function that returns if a number exist in a hash. 
Input: pointer to a hash and data to search for.
Output: 1 if positive. 0 if negative and if the hash is null or empty.
Error: */
int HashIsFound(const Hash* _hash, int data);

/*Desc.: function that returns the number of items in a hash. 
Input: pointer to a hash.
Output: the number of elements in the hash
Error: */
size_t HashNumOfItems(const Hash* _hash);

/*Desc.: function that returns the hash capacity to hold max elements. 
Input: pointer to a hash.
Output: size_ t num that represents the capacity of the hash.
Error: */
size_t HashCapacity(const Hash* _hash);

/*Desc.: function that returns the the average of collisions with existing numbers in hash while inserting new data.. 
Input: pointer to a hash.
Output: double num that represent the average collisions.
Error: */
double HashAverageCollisions(const Hash* _hash);

/*Desc.: function that returns the the max offset of numbers in th
Output: double num that represent the average collisions.
Input: pointer to a hash.
Output: size_t num that represent the max offset.
Error: */
size_t HashMaxCollisions(const Hash* _hash);

void HashPrint(const Hash* _hash);
    
#endif  /*__MYHASH__ */
