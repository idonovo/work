#include "../../inc/HashMap.h"
#include "../../inc/list_itr.h"
#include "../../inc/list_functions.h"

#include <stdio.h>
#include <stdlib.h>


#define SIZE 10

/***************print Functions***********************/
void PrintRes(size_t flag){

	if(flag != 0)
	{
		printf("PASS   :");
		return;
	}
	printf("FAIL   :");
	return;
}


size_t HashFunc(const void* _key){
    
    return *(int*)_key;  
}

int EqualityFunc(const void* _firstKey, const void* _secondKey){

    return  _firstKey == _secondKey? 1: 0;    
}

int PrintItems(const void* _key, void* _value, void* _contex){

    printf("val: %d   ", *(int*)_value);
    printf("key %d   ", *(int*)_key);
    return 1;
	
}

int ChangeVal(const void* _key, void* _value, void* _contex){

	*(int*)_value = *(int*)_contex;
	return 1;

}
/***************createFunctions***********************/	

void IsCreate(){
	
	HashMap* testHash = HashMapCreate(SIZE, HashFunc, EqualityFunc);
	PrintRes(testHash != NULL);
    printf("Is Create:\n");
    HashMapDestroy(&testHash, NULL, NULL);
    free(testHash);
    return;
}

void IsCreateNULLHashFunc(){
	
	HashMap* testHash = HashMapCreate(SIZE, NULL, EqualityFunc);
	PrintRes(testHash == NULL);
    printf("Is Create Null HashFunc:\n");
    return;
}

void IsCreateHashNullEqualFunc(){
	
	HashMap* testHash = HashMapCreate(SIZE, HashFunc, NULL);
	PrintRes(testHash == NULL);
    printf("IsCreate(HashNullEqualFunc:\n");
    return;
}

void IsDestroy(){
	
	HashMap* testHash = HashMapCreate(SIZE, HashFunc, EqualityFunc);
	HashMapDestroy(&testHash, NULL, NULL);
	PrintRes(testHash == NULL);
    printf("Is Destroy:\n");
    return;
}

void IsInsert(){
	
	HashMap* testHash = HashMapCreate(SIZE, HashFunc, EqualityFunc);
	int* x = malloc(sizeof(int));
	*x = 5;
	PrintRes(MAP_SUCCESS == HashMapInsert(testHash, (void*)x, (void*)x));
    printf("Is Insert:\n");
    HashMapDestroy(&testHash, NULL, NULL);
    return;
}

void IsInsertSameList(){
	
	int* x[11];
	int i;
	HashMap* testHash = HashMapCreate(5, HashFunc, EqualityFunc);
	
	for(i=0; i<10; i++)
	{
	    x[i] = malloc(sizeof(int));
	    *x[i] = i;
	    HashMapInsert(testHash, (void*)x[i], (void*)x[i]);
	}
	HashMapForEach(testHash, PrintItems, NULL);
	PrintRes(1);
    printf("Is InsertSamelist:\n");
    HashMapDestroy(&testHash, NULL, NULL);
    return;
}

void IsInsertNULLValue(){
	
	HashMap* testHash = HashMapCreate(SIZE, HashFunc, EqualityFunc);
	int* x = malloc(sizeof(int));
	*x = 5;
	PrintRes(MAP_SUCCESS == HashMapInsert(testHash, (void*)x, NULL));
    printf("Is InsertNULLValue:\n");
    HashMapDestroy(&testHash, NULL, NULL);
    return;
}

void IsInsertNULLKey(){
	
	HashMap* testHash = HashMapCreate(SIZE, HashFunc, EqualityFunc);
	int* x = malloc(sizeof(int));
	*x = 5;
	PrintRes(MAP_KEY_NULL_ERROR == HashMapInsert(testHash, NULL, (void*)x));
    printf("Is InsertNULLKey:\n");
    HashMapDestroy(&testHash, NULL, NULL);
    return;
}

void IsInsertDuplicateKey(){
	
	HashMap* testHash = HashMapCreate(5, HashFunc, EqualityFunc);
	int* x = malloc(sizeof(int));
	*x = 5;
	HashMapInsert(testHash, (void*)x, (void*)x);
	
	HashMapInsert(testHash, (void*)x, (void*)x);
	PrintRes(MAP_KEY_DUPLICATE_ERROR == HashMapInsert(testHash, (void*)x, (void*)x));
    printf("Is InsertDuplicateKey:\n");
    HashMapDestroy(&testHash, NULL, NULL);
    return;
}

void IsRehash(){
	
    int* x[10];
	int i;
	HashMap* testHash = HashMapCreate(5, HashFunc, EqualityFunc);
	
	for(i=0; i<10; i++)
	{
	    x[i] = malloc(sizeof(int));
	    *x[i] = i;
	    HashMapInsert(testHash, (void*)x[i], (void*)x[i]);
	}
	printf("before rehash:\n"); 
	HashMapForEach(testHash, PrintItems, NULL);
	printf("\n"); 
	PrintRes(HashMapRehash(testHash, 4) == MAP_SUCCESS);
    printf("Is Rehash:\n");
    HashMapForEach(testHash, PrintItems, NULL);
    printf("\n"); 
    HashMapDestroy(&testHash, NULL, NULL);
    
    return;
}

void IsRehashNULLHash(){
	
	PrintRes(HashMapRehash(NULL, 4) == MAP_UNINITIALIZED_ERROR);
    printf("Is Rehash NULL Hash:\n");
    
    return;
}


void IsRemove(){
	
    int* x[10];
	int i;
	int* pKey;
	int* pVal;
	HashMap* testHash = HashMapCreate(5, HashFunc, EqualityFunc);
	
	for(i=0; i<10; i++)
	{
	    x[i] = malloc(sizeof(int));
	    *x[i] = i;
	    HashMapInsert(testHash, (void*)x[i], (void*)x[i]);
	}
	pKey = malloc(sizeof(int));
	pVal = malloc(sizeof(int));
	
	PrintRes(HashMapRemove(testHash, (void*)x[0], ((void**)&pKey), ((void**)&pVal)) == MAP_SUCCESS);
    printf("Is Remove:\n");
    HashMapDestroy(&testHash, NULL, NULL);
    
    return;
}

void IsRemoveMiddleofList(){
	
    int* x[10];
	int i;
	int* pKey;
	int* pVal;
	HashMap* testHash = HashMapCreate(5, HashFunc, EqualityFunc);
	
	for(i=0; i<10; i++)
	{
	    x[i] = malloc(sizeof(int));
	    *x[i] = i;
	    HashMapInsert(testHash, (void*)x[i], (void*)x[i]);
	}
	pKey = malloc(sizeof(int));
	pVal = malloc(sizeof(int));
	
	PrintRes(HashMapRemove(testHash, (void*)x[1], ((void**)&pKey), ((void**)&pVal)) == MAP_SUCCESS);
    printf("Is RemoveMiddle ofHash:\n");
    HashMapDestroy(&testHash, NULL, NULL);
    
    return;
}

void IsRemoveNullKey(){
	
    int* x[10];
	int i;
	int* pKey;
	int* pVal;
	HashMap* testHash = HashMapCreate(5, HashFunc, EqualityFunc);
	
	for(i=0; i<10; i++)
	{
	    x[i] = malloc(sizeof(int));
	    *x[i] = i;
	    HashMapInsert(testHash, (void*)x[i], (void*)x[i]);
	}
	pKey = malloc(sizeof(int));
	pVal = malloc(sizeof(int));
	
	PrintRes(HashMapRemove(testHash, NULL, ((void**)&pKey), ((void**)&pVal)) == MAP_KEY_NULL_ERROR);
    printf("Is Remove NULL Key:\n");
    HashMapDestroy(&testHash, NULL, NULL);
    
    return;
}

void IsRemoveKeyNotFind(){
	
    int* x[10];
	int i;
	int* pKey;
	int* pVal;
	HashMap* testHash = HashMapCreate(5, HashFunc, EqualityFunc);
	
	for(i=0; i<9; i++)
	{
	    x[i] = malloc(sizeof(int));
	    *x[i] = i;
	    HashMapInsert(testHash, (void*)x[i], (void*)x[i]);
	}
	x[9] = malloc(sizeof(int));
	*x[9] = 21;
	pKey = malloc(sizeof(int));
	pVal = malloc(sizeof(int));
	
	PrintRes(HashMapRemove(testHash, (void*)x[9], ((void**)&pKey), ((void**)&pVal)) == MAP_KEY_NOT_FOUND_ERROR);
    printf("Is Remove Key Not Found:\n");
    HashMapDestroy(&testHash, NULL, NULL);
    
    return;
}

void IsFoundByKey(){
	
    int* x[10];
	int i;
	int* pVal;
	HashMap* testHash = HashMapCreate(5, HashFunc, EqualityFunc);
	
	for(i=0; i<10; i++)
	{
	    x[i] = malloc(sizeof(int));
	    *x[i] = i;
	    HashMapInsert(testHash, (void*)x[i], (void*)x[i]);
	}

	pVal = malloc(sizeof(int));
	
	PrintRes(HashMapFind(testHash, (void*)x[1], ((void**)&pVal)) == MAP_SUCCESS);
    printf("IsFoundByKey:\n");
    HashMapDestroy(&testHash, NULL, NULL);
    
    return;
}

void IsNotFoundByKey(){
	
    int* x[10];
	int i;

	int* pVal;
	HashMap* testHash = HashMapCreate(5, HashFunc, EqualityFunc);
	
	for(i=0; i<9; i++)
	{
	    x[i] = malloc(sizeof(int));
	    *x[i] = i;
	    HashMapInsert(testHash, (void*)x[i], (void*)x[i]);
	}
	x[9] = malloc(sizeof(int));
	*x[9] = 21;

	pVal = malloc(sizeof(int));
	
	PrintRes(HashMapFind(testHash, (void*)x[9], ((void**)&pVal)) == MAP_KEY_NOT_FOUND_ERROR);
    printf("IsNotFoundByKey:\n");
    HashMapDestroy(&testHash, NULL, NULL);
    
    return;
}

void IsFoundNullKey(){
	
	int* pVal;
	HashMap* testHash = HashMapCreate(5, HashFunc, EqualityFunc);
	
	PrintRes(HashMapFind(testHash, NULL, ((void**)&pVal)) == MAP_KEY_NULL_ERROR);
    printf("IsFoundNullKey:\n");
    HashMapDestroy(&testHash, NULL, NULL);
    
    return;
}

void IsFoundNullHash(){
	
	int* pVal;
	HashMap* testHash = HashMapCreate(5, HashFunc, EqualityFunc);
	
	PrintRes(HashMapFind(NULL, ((void*)&pVal), ((void**)&pVal)) == MAP_UNINITIALIZED_ERROR);
    printf("IsFoundNullHash:\n");
    HashMapDestroy(&testHash, NULL, NULL);
    
    return;
}

void IsReturnSize(){

	int* x[10];
	int i;
	HashMap* testHash = HashMapCreate(5, HashFunc, EqualityFunc);
	
	for(i=0; i<10; i++)
	{
	    x[i] = malloc(sizeof(int));
	    *x[i] = i;
	    HashMapInsert(testHash, (void*)x[i], (void*)x[i]);
	}
	PrintRes(HashMapSize(testHash) == 10);
    printf("IsReturnSize:\n");
    HashMapDestroy(&testHash, NULL, NULL);
    
    return;
}

void IsReturnSizeAfterRemove(){

	int* x[10];
	int i;
	int* pKey;
	int* pVal;
	HashMap* testHash = HashMapCreate(5, HashFunc, EqualityFunc);
	
	for(i=0; i<10; i++)
	{
	    x[i] = malloc(sizeof(int));
	    *x[i] = i;
	    HashMapInsert(testHash, (void*)x[i], (void*)x[i]);
	}
	pKey = malloc(sizeof(int));
	pVal = malloc(sizeof(int));
	
	HashMapRemove(testHash, (void*)x[4], ((void**)&pKey), ((void**)&pVal));
	PrintRes(HashMapSize(testHash) == 9);
    printf("IsReturnSizeAfterRemove:\n");
    HashMapDestroy(&testHash, NULL, NULL);
    
    return;
}

void IsChangeValforEach(){

	int* x[10];
	int* y[10];
	int i;
	HashMap* testHash = HashMapCreate(5, HashFunc, EqualityFunc);
	
	for(i=0; i<10; i++)
	{
	    x[i] = malloc(sizeof(int));
	    *x[i] = i;
	}
	for(i=0; i<10; i++)
	{
	    y[i] = malloc(sizeof(int));
	    *y[i] = i*2;
	    HashMapInsert(testHash, (void*)y[i], (void*)x[i]);
	}
	
	HashMapForEach(testHash,ChangeVal, (void*)x[5]);
	PrintRes(1);
    printf("IsChangeValforEach:\n");
    HashMapForEach(testHash, PrintItems, NULL);
    HashMapDestroy(&testHash, NULL, NULL);
    printf("\n");
    
	return;
}

void IsMapStats(){
 	
 	
 	int* x[40];
	int* y[40];
	int i;
	Map_Stats map;
	HashMap* testHash = HashMapCreate(14, HashFunc, EqualityFunc);
	
	for(i=0; i<40; i++)
	{
	    x[i] = malloc(sizeof(int));
	    *x[i] = i*2;
	}
	for(i=0; i<40; i++)
	{
	    y[i] = malloc(sizeof(int));
	    *y[i] = i*11;
	    HashMapInsert(testHash, (void*)y[i], (void*)x[i]);
	}
	
	map = HashMapGetStatistics(testHash);
	
	printf("\nstats:\npairs: %u\n", map.pairs);
	printf("buckets: %u\n", map.buckets);
	printf("chains: %u\n", map.chains);
	printf("collisions: %u\n", map.collisions);
	printf("maxChainLength: %u\n", map.maxChainLength);
	printf("averageChainLength: %u\n", map.averageChainLength);
	
	HashMapDestroy(&testHash, NULL, NULL);
	
	return;
}

int main(){

	IsCreate();
	IsCreateNULLHashFunc();
	IsCreateHashNullEqualFunc();
	
	IsDestroy();
	
	IsInsert();
	IsInsertSameList();
	IsInsertNULLValue();
	IsInsertNULLKey();
    IsInsertDuplicateKey();
    
    IsRehash();
    IsRehashNULLHash();
    
    IsRemove();
    IsRemoveMiddleofList();
    IsRemoveNullKey();
    IsRemoveKeyNotFind();
    
    IsFoundByKey();
    IsNotFoundByKey();
    IsFoundNullKey();
    IsFoundNullHash();
    
    IsReturnSize();
    IsReturnSizeAfterRemove();
    
    IsChangeValforEach();
    
    IsMapStats();

	return 0;
}

