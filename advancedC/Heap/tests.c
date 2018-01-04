
/*           Heap API functions tests - by Ido Naveh            */ 
  
#include "../../inc/Heap.h"

# include <stdio.h>
# include <stdlib.h>


/****************UserActionFunc/PredicateFunc**************/
void _destoryFunc(void* _elemant){
	
	free(_elemant);
	
	return;
}

int PrinItems(const void* _element, void* _context){
	
	printf("%3d", *(int*)_element);

	return 1;
}

int PrintVec(void* _element, void* _context){
	
	printf("%3d", *(int*)_element);

	return 1;
}


int PrinChars(const void* _element, void* _context){
	
	printf("%3c", *(char*)_element);

	return 1;
}


int Compare(const void *_left, const void *_right){

    if(*(int*)_left < *(int*)_right)
    {
        return 1;
    }
    return 0;
}

int CompareChars(const void *_left, const void *_right){

    if(*(char*)_left < *(char*)_right)
    {
        return 1;
    }
    return 0;
}

/***************print test resault***********************/
void PrintRes(size_t flag){

	if(flag != 0)
	{
		printf("PASS   :");
		return;
	}
	printf("FAIL   :");
	return;
}



/*_________________BuildHeap Tests________________*/
void IsBuild(){
	
	int* a[5];
	Vector* testVector;
	Heap* testHeap;
	testVector = VectorCreate(10, 10);
	a[0] = malloc(sizeof(int));
    *a[0] = 5;
     VectorAppend(testVector, (void*)a[0]);
    a[1] = malloc(sizeof(int));
    *a[1] =3;
   	 VectorAppend(testVector, (void*)a[1]);
    a[2] = malloc(sizeof(int));
    *a[2] =7;
   	 VectorAppend(testVector, (void*)a[2]);
    a[3] = malloc(sizeof(int));
    *a[3] =4;
     VectorAppend(testVector, (void*)a[3]);
    a[4] = malloc(sizeof(int));
    *a[4] =6;
    VectorAppend(testVector, (void*)a[4]);
	testHeap = HeapBuild(testVector, Compare);
	PrintRes(testHeap != NULL);
	printf("IsBuild\n");
	HeapForEach(testHeap, PrinItems, NULL);
	printf("\n");
	HeapDestroy(&testHeap);
	VectorDestroy(&testVector, _destoryFunc);
	return;
}	

void IsBuildDecrementValue(){

	int* a[5];
	Vector* testVector;
	Heap* testHeap;
	testVector = VectorCreate(10, 10);
	a[0] = malloc(sizeof(int));
    *a[0] = 9;
     VectorAppend(testVector, (void*)a[0]);
    a[1] = malloc(sizeof(int));
    *a[1] =8;
   	 VectorAppend(testVector, (void*)a[1]);
    a[2] = malloc(sizeof(int));
    *a[2] =7;
   	 VectorAppend(testVector, (void*)a[2]);
    a[3] = malloc(sizeof(int));
    *a[3] =6;
     VectorAppend(testVector, (void*)a[3]);
    a[4] = malloc(sizeof(int));
    *a[4] =3;
    VectorAppend(testVector, (void*)a[4]);
	testHeap = HeapBuild(testVector, Compare);
	PrintRes(testHeap != NULL);
	printf("IsBuildDecrementValue\n");
	HeapForEach(testHeap, PrinItems, NULL);
	printf("\n");
	HeapDestroy(&testHeap);
	VectorDestroy(&testVector, _destoryFunc);
	return;
}	


void IsBuildIncrementValue(){

	int* a[5];
	Vector* testVector;
	Heap* testHeap;
	testVector = VectorCreate(10, 10);
	a[0] = malloc(sizeof(int));
    *a[0] = 9;
     VectorAppend(testVector, (void*)a[0]);
    a[1] = malloc(sizeof(int));
    *a[1] =12;
   	 VectorAppend(testVector, (void*)a[1]);
    a[2] = malloc(sizeof(int));
    *a[2] =18;
   	 VectorAppend(testVector, (void*)a[2]);
    a[3] = malloc(sizeof(int));
    *a[3] =19;
     VectorAppend(testVector, (void*)a[3]);
    a[4] = malloc(sizeof(int));
    *a[4] =30;
    VectorAppend(testVector, (void*)a[4]);
	testHeap = HeapBuild(testVector, Compare);
	PrintRes(testHeap != NULL);
	printf("IsBuildIncrementValue\n");
	HeapForEach(testHeap, PrinItems, NULL);
	printf("\n");
	HeapDestroy(&testHeap);
	VectorDestroy(&testVector, _destoryFunc);
	return;
}

void IsBuildNULLVector(){
    
    Heap* testHeap;
	testHeap = HeapBuild(NULL, Compare);
	PrintRes(testHeap == NULL);
	printf("IsBuildNULLVector\n");
	
	return;
}

/*_________________InsretHeap Tests________________*/

void IsInsertAndBubbleUp(){

	int* a[6];
	Vector* testVector;
	Heap* testHeap;
	testVector = VectorCreate(10, 10);
	a[0] = malloc(sizeof(int));
    *a[0] = 9;
     VectorAppend(testVector, (void*)a[0]);
    a[1] = malloc(sizeof(int));
    *a[1] =12;
   	 VectorAppend(testVector, (void*)a[1]);
    a[2] = malloc(sizeof(int));
    *a[2] =18;
   	 VectorAppend(testVector, (void*)a[2]);
    a[3] = malloc(sizeof(int));
    *a[3] =19;
     VectorAppend(testVector, (void*)a[3]);
    a[4] = malloc(sizeof(int));
    *a[4] =30;
    VectorAppend(testVector, (void*)a[4]);
	testHeap = HeapBuild(testVector, Compare);
	 a[5] = malloc(sizeof(int));
    *a[5] =22;
	PrintRes(HeapInsert(testHeap, (void*)a[5]) == HEAP_SUCCESS);
	printf("IsInsertAndBubble\n");
	HeapForEach(testHeap, PrinItems, NULL);
	printf("\n");
	HeapDestroy(&testHeap);
	VectorDestroy(&testVector, _destoryFunc);
	return;

}

void IsInsertNullHeap(){
    
    void* x = NULL;
    PrintRes(HeapInsert(NULL, x) == HEAP_NOT_INITIALIZED);
	printf("IsInsertNullHeap\n");

	return;
}

void IsInsertNullItem(){
    
    int* a[6];
	Vector* testVector;
	Heap* testHeap;
	testVector = VectorCreate(10, 10);
	a[0] = malloc(sizeof(int));
    *a[0] = 9;
     VectorAppend(testVector, (void*)a[0]);
    a[1] = malloc(sizeof(int));
    *a[1] =12;
   	 VectorAppend(testVector, (void*)a[1]);
    a[2] = malloc(sizeof(int));
    *a[2] =18;
   	 VectorAppend(testVector, (void*)a[2]);
    a[3] = malloc(sizeof(int));
    *a[3] =19;
     VectorAppend(testVector, (void*)a[3]);
    a[4] = malloc(sizeof(int));
    *a[4] =30;
    VectorAppend(testVector, (void*)a[4]);
	testHeap = HeapBuild(testVector, Compare);
    PrintRes(HeapInsert(testHeap, NULL) == HEAP_INV_ARG);
	printf("IsInsertNullHeap\n");
	printf("\n");
	HeapDestroy(&testHeap);
	VectorDestroy(&testVector, _destoryFunc);
	return;
}

void IsInsertAfterInsert(){

    int* a[7];
	Vector* testVector;
	Heap* testHeap;
	testVector = VectorCreate(10, 10);
	a[0] = malloc(sizeof(int));
    *a[0] = 9;
     VectorAppend(testVector, (void*)a[0]);
    a[1] = malloc(sizeof(int));
    *a[1] =12;
   	 VectorAppend(testVector, (void*)a[1]);
    a[2] = malloc(sizeof(int));
    *a[2] =18;
   	 VectorAppend(testVector, (void*)a[2]);
    a[3] = malloc(sizeof(int));
    *a[3] =19;
     VectorAppend(testVector, (void*)a[3]);
    a[4] = malloc(sizeof(int));
    *a[4] =30;
    VectorAppend(testVector, (void*)a[4]);
	testHeap = HeapBuild(testVector, Compare);
	 a[5] = malloc(sizeof(int));
    *a[5] =15;
    HeapInsert(testHeap, (void*)a[5]);
     a[6] = malloc(sizeof(int));
    *a[6] =21;
	PrintRes(HeapInsert(testHeap, (void*)a[6]) == HEAP_SUCCESS);
	printf("IsInsertAfterInsert\n");
	HeapForEach(testHeap, PrinItems, NULL);
	printf("\n");
	HeapDestroy(&testHeap);
	VectorDestroy(&testVector, _destoryFunc);
	return;

}

void IsInsertSameNum(){

    int* a[7];
	Vector* testVector;
	Heap* testHeap;
	testVector = VectorCreate(10, 10);
	a[0] = malloc(sizeof(int));
    *a[0] = 9;
     VectorAppend(testVector, (void*)a[0]);
    a[1] = malloc(sizeof(int));
    *a[1] =12;
   	 VectorAppend(testVector, (void*)a[1]);
    a[2] = malloc(sizeof(int));
    *a[2] =18;
   	 VectorAppend(testVector, (void*)a[2]);
    a[3] = malloc(sizeof(int));
    *a[3] =19;
     VectorAppend(testVector, (void*)a[3]);
    a[4] = malloc(sizeof(int));
    *a[4] =30;
    VectorAppend(testVector, (void*)a[4]);
	testHeap = HeapBuild(testVector, Compare);
	 a[5] = malloc(sizeof(int));
    *a[5] =15;
    HeapInsert(testHeap, (void*)a[5]);
     a[6] = malloc(sizeof(int));
    *a[6] =18;
	PrintRes(HeapInsert(testHeap, (void*)a[6]) == HEAP_SUCCESS);
	printf("IsInsertSameNum\n");
	HeapForEach(testHeap, PrinItems, NULL);
	printf("\n");
	HeapDestroy(&testHeap);
	VectorDestroy(&testVector, _destoryFunc);
	return;

}

void IsGetHeapPeak(){
	
	int* a[5];
	Vector* testVector;
	Heap* testHeap;
	testVector = VectorCreate(10, 10);
	a[0] = malloc(sizeof(int));
    *a[0] = 5;
     VectorAppend(testVector, (void*)a[0]);
    a[1] = malloc(sizeof(int));
    *a[1] =3;
   	 VectorAppend(testVector, (void*)a[1]);
    a[2] = malloc(sizeof(int));
    *a[2] =7;
   	 VectorAppend(testVector, (void*)a[2]);
    a[3] = malloc(sizeof(int));
    *a[3] =4;
     VectorAppend(testVector, (void*)a[3]);
    a[4] = malloc(sizeof(int));
    *a[4] =6;
    VectorAppend(testVector, (void*)a[4]);
	testHeap = HeapBuild(testVector, Compare);
	PrintRes(*(int*)HeapPeek(testHeap) == 7);
	printf("IsGetPeak\n");
	HeapDestroy(&testHeap);
	VectorDestroy(&testVector, _destoryFunc);
	return;
}	

void IsGetPeakNullHeap(){
    
	PrintRes(HeapPeek(NULL) == NULL);
	printf("IsBGetPeakNULLHeap\n");
	return;
}

void IsGetHeapSize(){
	
	int* a[5];
	Vector* testVector;
	Heap* testHeap;
	testVector = VectorCreate(10, 10);
	a[0] = malloc(sizeof(int));
    *a[0] = 5;
     VectorAppend(testVector, (void*)a[0]);
    a[1] = malloc(sizeof(int));
    *a[1] =3;
   	 VectorAppend(testVector, (void*)a[1]);
    a[2] = malloc(sizeof(int));
    *a[2] =7;
   	 VectorAppend(testVector, (void*)a[2]);
    a[3] = malloc(sizeof(int));
    *a[3] =4;
     VectorAppend(testVector, (void*)a[3]);
    a[4] = malloc(sizeof(int));
    *a[4] =6;
    VectorAppend(testVector, (void*)a[4]);
	testHeap = HeapBuild(testVector, Compare);
	PrintRes(HeapSize(testHeap) == 5);
	printf("IsBGetHeapSize\n");
	HeapDestroy(&testHeap);
	VectorDestroy(&testVector, _destoryFunc);
	return;
}	

void IsGetHeapSizeNullHeap(){
    
	PrintRes(HeapPeek(NULL) == 0);
	printf("IsHeapSizeNULLHeap\n");
	return;
}

void IsExtractMax(){

    int* a[5];
	Vector* testVector;
	Heap* testHeap;
	testVector = VectorCreate(10, 10);
	a[0] = malloc(sizeof(int));
    *a[0] = 9;
     VectorAppend(testVector, (void*)a[0]);
    a[1] = malloc(sizeof(int));
    *a[1] =12;
   	 VectorAppend(testVector, (void*)a[1]);
    a[2] = malloc(sizeof(int));
    *a[2] =18;
   	 VectorAppend(testVector, (void*)a[2]);
    a[3] = malloc(sizeof(int));
    *a[3] =19;
     VectorAppend(testVector, (void*)a[3]);
    a[4] = malloc(sizeof(int));
    *a[4] =30;
    VectorAppend(testVector, (void*)a[4]);
	testHeap = HeapBuild(testVector, Compare);
    PrintRes(1);
	printf("IsExtractMax\n");
	HeapForEach(testHeap, PrinItems, NULL);
	printf("\n");
	HeapExtract(testHeap);
	HeapForEach(testHeap, PrinItems, NULL);
	printf("\n");
	HeapDestroy(&testHeap);
	VectorDestroy(&testVector, _destoryFunc);
	return;

}

void IsHeapSort(){
  
    int* a[10];
	Vector* testVector;
	testVector = VectorCreate(10, 10);
	a[0] = malloc(sizeof(int));
    *a[0] = 56;
     VectorAppend(testVector, (void*)a[0]);
    a[1] = malloc(sizeof(int));
    *a[1] =12;
   	 VectorAppend(testVector, (void*)a[1]);
    a[2] = malloc(sizeof(int));
    *a[2] =18;
   	 VectorAppend(testVector, (void*)a[2]);
    a[3] = malloc(sizeof(int));
    *a[3] =7;
     VectorAppend(testVector, (void*)a[3]);
    a[4] = malloc(sizeof(int));
    *a[4] =101;
    VectorAppend(testVector, (void*)a[4]);
    a[5] = malloc(sizeof(int));
    *a[5] = 45;
     VectorAppend(testVector, (void*)a[5]);
    a[6] = malloc(sizeof(int));
    *a[6] =7;
   	 VectorAppend(testVector, (void*)a[6]);
    a[7] = malloc(sizeof(int));
    *a[7] =90;
   	 VectorAppend(testVector, (void*)a[7]);
    a[8] = malloc(sizeof(int));
    *a[8] =222;
     VectorAppend(testVector, (void*)a[8]);
    a[9] = malloc(sizeof(int));
    *a[9] =77;
    VectorAppend(testVector, (void*)a[9]);
    HeapSort(testVector, Compare);
    PrintRes(1);
	printf("IsHeapSort\n");
	VectorForEach(testVector, PrintVec, NULL);
	printf("\n");
	VectorDestroy(&testVector, _destoryFunc);
	return;

}

void IsHeapSortNegValue(){
  
    int* a[10];
	Vector* testVector;
	testVector = VectorCreate(10, 10);
	a[0] = malloc(sizeof(int));
    *a[0] = -56;
     VectorAppend(testVector, (void*)a[0]);
    a[1] = malloc(sizeof(int));
    *a[1] =-12;
   	 VectorAppend(testVector, (void*)a[1]);
    a[2] = malloc(sizeof(int));
    *a[2] =-18;
   	 VectorAppend(testVector, (void*)a[2]);
    a[3] = malloc(sizeof(int));
    *a[3] =-7;
     VectorAppend(testVector, (void*)a[3]);
    a[4] = malloc(sizeof(int));
    *a[4] =-101;
    VectorAppend(testVector, (void*)a[4]);
    a[5] = malloc(sizeof(int));
    *a[5] = -45;
     VectorAppend(testVector, (void*)a[5]);
    a[6] = malloc(sizeof(int));
    *a[6] =-7;
   	 VectorAppend(testVector, (void*)a[6]);
    a[7] = malloc(sizeof(int));
    *a[7] =-22;
   	 VectorAppend(testVector, (void*)a[7]);
    a[8] = malloc(sizeof(int));
    *a[8] =-222;
     VectorAppend(testVector, (void*)a[8]);
    a[9] = malloc(sizeof(int));
    *a[9] =-77;
    VectorAppend(testVector, (void*)a[9]);
    HeapSort(testVector, Compare);
    PrintRes(1);
	printf("IsHeapSortNegValue\n");
	VectorForEach(testVector, PrintVec, NULL);
	printf("\n");
	VectorDestroy(&testVector, _destoryFunc);
	return;

}

void IsHeapSortNoCompareFunc(){
  
    int* a[10];
	Vector* testVector;
	testVector = VectorCreate(10, 10);
	a[0] = malloc(sizeof(int));
    *a[0] = -56;
     VectorAppend(testVector, (void*)a[0]);
    a[1] = malloc(sizeof(int));
    *a[1] =-12;
   	 VectorAppend(testVector, (void*)a[1]);
    a[2] = malloc(sizeof(int));
    *a[2] =-18;
   	 VectorAppend(testVector, (void*)a[2]);
    a[3] = malloc(sizeof(int));
    *a[3] =-7;
     VectorAppend(testVector, (void*)a[3]);
    a[4] = malloc(sizeof(int));
    *a[4] =-101;
    VectorAppend(testVector, (void*)a[4]);
    a[5] = malloc(sizeof(int));
    *a[5] = -45;
     VectorAppend(testVector, (void*)a[5]);
    a[6] = malloc(sizeof(int));
    *a[6] =-7;
   	 VectorAppend(testVector, (void*)a[6]);
    a[7] = malloc(sizeof(int));
    *a[7] =-22;
   	 VectorAppend(testVector, (void*)a[7]);
    a[8] = malloc(sizeof(int));
    *a[8] =-222;
     VectorAppend(testVector, (void*)a[8]);
    a[9] = malloc(sizeof(int));
    *a[9] =-77;
    VectorAppend(testVector, (void*)a[9]);
    HeapSort(testVector, NULL);
    PrintRes(1);
	printf("IsHeapSortNoCompareFunc\n");
	VectorForEach(testVector, PrintVec, NULL);
	printf("\n");
	VectorDestroy(&testVector, _destoryFunc);
	return;

}


void IsExtractNullHeap(){
    
	PrintRes(HeapExtract(NULL) == NULL);
	printf("IsHeapSizeNULLHeap\n");
	return;
}

void IsHeapforEchChars(){

    char* a[7];
	Vector* testVector;
	Heap* testHeap;
	testVector = VectorCreate(10, 10);
	a[0] = malloc(sizeof(int));
    *a[0] = 'a';
     VectorAppend(testVector, (void*)a[0]);
    a[1] = malloc(sizeof(int));
    *a[1] ='d';
   	 VectorAppend(testVector, (void*)a[1]);
    a[2] = malloc(sizeof(int));
    *a[2] ='p';
   	 VectorAppend(testVector, (void*)a[2]);
    a[3] = malloc(sizeof(int));
    *a[3] ='q';
     VectorAppend(testVector, (void*)a[3]);
    a[4] = malloc(sizeof(int));
    *a[4] ='c';
    VectorAppend(testVector, (void*)a[4]);
	testHeap = HeapBuild(testVector,CompareChars);
	 a[5] = malloc(sizeof(int));
    *a[5] ='i';
    HeapInsert(testHeap, (void*)a[5]);
     a[6] = malloc(sizeof(int));
    *a[6] ='d';
	PrintRes(HeapInsert(testHeap, (void*)a[6]) == HEAP_SUCCESS);
	printf("IsIHeap_ForEachChars\n");
	HeapForEach(testHeap, PrinChars, NULL);
	printf("\n");
	HeapDestroy(&testHeap);
	VectorDestroy(&testVector, _destoryFunc);
	return;

}

void IsHeap_ForEachNULLHeap(){

	PrintRes(HeapForEach(NULL, PrinChars, NULL) == 0);
	printf("IsIHeap_ForEachNULLHeap\n");
	return;
}


int main(){

	IsBuild();
	IsBuildDecrementValue();
	IsBuildIncrementValue();
	IsBuildNULLVector();
	
	
	IsInsertAndBubbleUp();
	IsInsertAfterInsert();
	IsInsertNullHeap();
	IsInsertNullItem();
	IsInsertSameNum();
	
	IsGetHeapPeak();
	IsGetPeakNullHeap();
	
	IsGetHeapSize();
	IsGetHeapSizeNullHeap();
	
	IsExtractMax();
	IsExtractNullHeap();
	
	IsHeapSort();
	IsHeapSortNegValue();
	IsHeapSortNoCompareFunc();
	
	IsHeapforEchChars();
	IsHeap_ForEachNULLHeap();
	return 0;
}


