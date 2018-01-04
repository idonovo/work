/*           Heap API functions tests - by Ido Naveh            */   

# include <stdio.h>
# include <stdlib.h>

# include "heap.h"

#define MAGIC 7377175
#define SIZE 10

/*_________________BuildHeap Tests________________*/
void IsBuild(){
	
	Vector* testVector;
	testVector = VectorCreate(SIZE, SIZE);
	VectorAdd(testVector, SIZE+1);
	VectorAdd(testVector, SIZE-2);
	VectorAdd(testVector, SIZE);
	VectorAdd(testVector, SIZE-10);
	VectorAdd(testVector, SIZE+9);
	VectorAdd(testVector, SIZE);
	VectorAdd(testVector, SIZE-5);
	Heap* testHeap = HeapBuild(testVector);
    printf("Is Build:");
	if (testHeap != NULL){
		printf("PASS\n");
		HeapPrint(testHeap);
		HeapDestroy(testHeap);
		return;
	}
	printf("FAIL\n");
	return;
}	

void IsBuildDecrementValue(){

	Vector* testVector;
	testVector = VectorCreate(SIZE, SIZE);
	VectorAdd(testVector, SIZE+1);
	VectorAdd(testVector, SIZE-2);
	VectorAdd(testVector, SIZE-5);
	VectorAdd(testVector, SIZE-6);
	VectorAdd(testVector, SIZE-7);
	VectorAdd(testVector, SIZE-9);
	VectorAdd(testVector, SIZE-12);
	Heap* testHeap = HeapBuild(testVector);
    printf("Is Build With Decrease Value:");
	if (testHeap != NULL){
		printf("PASS\n");
		HeapPrint(testHeap);
		HeapDestroy(testHeap);
		return;
	}
	printf("FAIL\n");
	return;
}	

void IsBuildOneLeaf(){

	Vector* testVector;
	testVector = VectorCreate(SIZE, SIZE);
	VectorAdd(testVector, SIZE+1);
	VectorAdd(testVector, SIZE-2);
	VectorAdd(testVector, SIZE-5);
	VectorAdd(testVector, SIZE);
	VectorAdd(testVector, SIZE-7);
	VectorAdd(testVector, SIZE+6);
	Heap* testHeap = HeapBuild(testVector);
    printf("Is Build With One Leaf:");
	if (testHeap != NULL){
		printf("PASS\n");
		HeapPrint(testHeap);
		HeapDestroy(testHeap);
		return;
	}
	printf("FAIL\n");
	return;
}

/*_________________InsretHeap Tests________________*/

void IsInsertAndBubbleUp(){


	Vector* testVector;
	testVector = VectorCreate(SIZE, SIZE);
	VectorAdd(testVector, SIZE+1);
	VectorAdd(testVector, SIZE-2);
	VectorAdd(testVector, SIZE-5);
	Heap* testHeap = HeapBuild(testVector);
    printf("Is Insert:");
    HeapPrint(testHeap);
	if (HeapInsert(testHeap, SIZE)== ERR_OK){
		printf("PASS\n");
		HeapPrint(testHeap);
		HeapDestroy(testHeap);
		return;
	}
	printf("FAIL\n");
	return;
}

void IsInsertNullHeap(){

	Heap* testHeap = NULL;
    printf("Is Insert NULL Heap:");
	if (HeapInsert(testHeap, SIZE) == ERR_NOT_INITIALIZED){
		printf("PASS\n");
		return;
	}
	printf("FAIL\n");
	return;
}

void IsGetHeapMax(){
    
    int max;
    Vector* testVector;
	testVector = VectorCreate(SIZE, SIZE);
	VectorAdd(testVector, SIZE-8);
	VectorAdd(testVector, SIZE-2);
	VectorAdd(testVector, SIZE-5);
	Heap* testHeap = HeapBuild(testVector);
	HeapMax(testHeap, &max);
    printf("Is Get Heap Max:");
	if (max == SIZE-5){
		printf("PASS\n");
		HeapDestroy(testHeap);
		return;
	}
	printf("FAIL\n");
	HeapDestroy(testHeap);
	return;

}

void IsGetMaxNullHeap(){
    
    int max;	
    Heap* testHeap = NULL;
    printf("Is Get Max NULL Heap:");
	if (HeapMax(testHeap, &max) == ERR_NOT_INITIALIZED){
		printf("PASS\n");
		return;
	}
	printf("FAIL\n");
	return;
}

void IsExtractMax(){
    
    int max;
    Vector* testVector;
	testVector = VectorCreate(SIZE, SIZE);
	VectorAdd(testVector, SIZE+1);
	VectorAdd(testVector, SIZE-2);
	VectorAdd(testVector, SIZE-5);
	VectorAdd(testVector, SIZE);
	VectorAdd(testVector, SIZE-7);
	VectorAdd(testVector, SIZE+6);
	Heap* testHeap = HeapBuild(testVector);
	printf("Is Extract Max:");
	if (HeapExtractMax(testHeap,&max)== ERR_OK){
		printf("PASS\n");
		HeapDestroy(testHeap);
		return;
	}
	printf("FAIL\n");
	HeapDestroy(testHeap);
	return;
}

void IsExtractMaxNull(){
    
    int max;
    Vector* testVector;
	testVector = VectorCreate(SIZE, SIZE);
	Heap* testHeap = NULL;
	printf("Is Extract Max Null Heap:");
	if (HeapExtractMax(testHeap,&max)== ERR_NOT_INITIALIZED){
		printf("PASS\n");
		return;
	}
	printf("FAIL\n");
	return;
}

void IsReturnItemsNum(){

    int max;
    Vector* testVector;
	testVector = VectorCreate(SIZE, SIZE);
	VectorAdd(testVector, SIZE+1);
	VectorAdd(testVector, SIZE-2);
	VectorAdd(testVector, SIZE-5);
	VectorAdd(testVector, SIZE);
	VectorAdd(testVector, SIZE-7);
	VectorAdd(testVector, SIZE+6);
	Heap* testHeap = HeapBuild(testVector);
	printf("Is Return Items Num:");
	max = HeapItemsNum(testHeap);
	if (max == 6){
		printf("PASS\n");
		HeapDestroy(testHeap);
		return;
	}
	printf("FAIL\n");
	HeapDestroy(testHeap);
	return;

}
int main(){

	IsBuild();
    IsBuildDecrementValue();
    IsBuildOneLeaf();
    
    IsInsertAndBubbleUp();
    IsInsertNullHeap();
    
    IsGetHeapMax();
    IsGetMaxNullHeap();
    
    IsExtractMax();
    IsExtractMaxNull();
    
    IsReturnItemsNum();
	return 0;
}


	
