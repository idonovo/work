#include <stdio.h>
#include <stdlib.h>

#include "../../inc/double.h"
#include "../../inc/list_itr.h"
#include "../../inc/list_functions.h"


/****************UserActionFunc/PredicateFunc**************/
int _destoryFunc(void* _elemant, void* _context){
	
	free(_elemant);
	
	return 0;
}

int Match(void* _element, void* _context){
	
	if(*(int*)_element == *(int*)_context)
	{
		return 1;
	}
	return 0;
}

int Increment(void* _element, void* _context){
	
	*(int*)_element += *(int*)_context;
	printf("%3d", *(int*)_element);

	return 1;
}

int PrinItems(void* _element, void* _context){
	
	printf("%3d\n", *(int*)_element);

	return 1;
}

int CompareIntS(void* _a, void* _b){
	
	if(*(int*)_a < *(int*)_b)
	{
		return 1;
	}
	return 0;
}

int PutStr(void* _element, void* _context){
	
	*(char*)_element = *(char*)_context;

	return 1;
}

int CompareCharS(void* _a, void* _b){
	
	if(*(char*)_a < *(char*)_b)
	{
		return 1;
	}
	return 0;
}

int PrinCharItems(void* _element, void* _context){
	
	printf("%3c", *(char*)_element);

	return 1;
}

int IsEqual(void* _a, void* _b){
	
	if(*(int*)_a == *(int*)_b)
	{
		return 0;
	}
	return 1;
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

/**********************************list_itr.h API tests**********/


void IsListIterBegin(){

	int* x[3], i;
	void* z = NULL; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<3; i++)
	{
		x[i] = malloc(sizeof(int));
		*x[i] = 5;
		ListPushHead(testlist,(void*)x[i]);
	}
	z = ListItr_Begin(testlist);
	PrintRes(z != NULL);
	printf(" IsListIterBegin\n");
    ListDestroy(&testlist, _destoryFunc);
	return;
}

void IsListIterBeginNULL(){
    
    void* z = NULL;
	z = ListItr_Begin(NULL);
	PrintRes(z == NULL);
	printf(" IsListIterBeginNULL\n");
	return;
}

void IsListIterEnd(){

	int* x[3], i;
	void* z = NULL; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<3; ++i)
	{
		x[i] = malloc(sizeof(int));
		*x[i] = 5;
		ListPushHead(testlist,(void*)x[i]);
	}
	z = ListItr_End(testlist);
	PrintRes(z != NULL);
	printf(" IsListIterEnd\n");
    ListDestroy(&testlist, _destoryFunc);
	return;
}

void IsListIterEndNULL(){
    
    void* z;
	z = ListItr_End(NULL);
	PrintRes(z == NULL);
	printf(" IsListIterBeginNULL\n");
	return;
}

void IsGetEqual(){

	int* x;
	void* z[2]; 
	
	List* testlist = ListCreate();
	
	x = malloc(sizeof(int));
	*x= 2;
	ListPushHead(testlist,(void*)x);
	z[0] = ListItr_Begin(testlist);
	z[1] = ListItr_Begin(testlist);

	PrintRes(ListItr_Equals(z[1], z[0]));
	printf(" IsGetEqual\n");
    ListDestroy(&testlist, _destoryFunc);
	return;
}

void IsGetNotEqual(){

	int* x[2];
	void* z[2]; 
	
	List* testlist = ListCreate();
	
	x[0] = malloc(sizeof(int));
	*x[0]= 5;
	ListPushHead(testlist,(void*)x[0]);
	z[0] = ListItr_Begin(testlist);
	
	x[1] = malloc(sizeof(int));
	*x[1]= 5;	
    ListPushHead(testlist,(void*)x[0]);	
	z[1] = ListItr_Begin(testlist);

	PrintRes(!ListItr_Equals(z[1], z[0]));
	printf(" IsGetNotEqual\n");
    ListDestroy(&testlist, NULL);
	return;
}

void IsGetNext(){

	int* x[4], i;
	void* z[2]; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<4; ++i)
	{
		x[i] = malloc(sizeof(int));
		*x[i]= i;
		ListPushHead(testlist,(void*)x[i]);
	} 
	z[0] = ListItr_Begin(testlist);
	z[1] = ListItr_Begin(testlist);
	z[1] = ListItr_Next(z[1]);

	PrintRes(z[0] != z[1]);
	printf("IsGetNext\n");
    ListDestroy(&testlist, _destoryFunc);
	return;
}

void IsGetNextTail(){

	int* x[4], i;
	void* z; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<4; ++i)
	{
		x[i] = malloc(sizeof(int));
		*x[i]= i;
		ListPushHead(testlist,(void*)x[i]);
	} 
	z = ListItr_End(testlist);
	z = ListItr_Next(z);

	PrintRes(NULL == z);
	printf("IsGetNextTail\n");
    ListDestroy(&testlist, _destoryFunc);
	return;
}

void IsGetPrev(){

	int* x[4], i;
	void* z[2]; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<4; ++i)
	{
		x[i] = malloc(sizeof(int));
		*x[i]= i;
		ListPushHead(testlist,(void*)x[i]);
	} 
	z[0] = ListItr_Begin(testlist);
	z[1] = ListItr_Begin(testlist);
	z[0] = ListItr_Prev(z[0]);

	PrintRes(z[0] == z[1]);
	printf("IsGetPrev\n");
    ListDestroy(&testlist, _destoryFunc);
	return;
}

void IsGetPrevHead(){

	int* x[4], i;
	void* z; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<4; ++i)
	{
		x[i] = malloc(sizeof(int));
		*x[i]= i;
		ListPushHead(testlist,(void*)x[i]);
	} 
	z = ListItr_Begin(testlist);
	z = ListItr_Prev(z);

	PrintRes(NULL != z);
	printf("IsGetPrevHead\n");
    ListDestroy(&testlist, _destoryFunc);
	return;
}


void IsGetVal(){

	int* x[4], i;
	void* z[2]; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<4; ++i)
	{
		x[i] = malloc(sizeof(int));
		*x[i]= 10;
		ListPushHead(testlist,(void*)x[i]);
	} 

	z[0] = ListItr_Begin(testlist);
	z[1] = ListItr_Get(z[0]);

	PrintRes(10 == *(int*)z[1]);
	printf("IsGetVal\n");
    ListDestroy(&testlist, _destoryFunc);
	return;
}

void IsGetValTail(){

	int* x[4], i;
	void* z[2]; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<4; ++i)
	{
		x[i] = malloc(sizeof(int));
		*x[i]= 10;
		ListPushHead(testlist,(void*)x[i]);
	} 

	z[0] = ListItr_End(testlist);
	z[1] = ListItr_Get(z[0]);

	PrintRes(NULL == z[1]);
	printf("IsGetValtail\n");
    ListDestroy(&testlist, _destoryFunc);
	return;
}

void IsGetValHead(){

	int* x[4], i;
	void* z[2]; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<4; ++i)
	{
		x[i] = malloc(sizeof(int));
		*x[i]= 10;
		ListPushHead(testlist,(void*)x[i]);
	} 

	z[0] = ListItr_Begin(testlist);
	z[0] = ListItr_Prev(z[0]);
	z[1] = ListItr_Get(z[0]);

	PrintRes(NULL != z[1]);
	printf("IsGetValHead\n");
    ListDestroy(&testlist, _destoryFunc);
	return;
}

void IsSetVal(){

	int* x[4], i;
	void* z[3]; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<4; ++i)
	{
		x[i] = malloc(sizeof(int));
		*x[i]= 10;
		ListPushHead(testlist,(void*)x[i]);
	} 
	
    z[2]  = &i;
	z[0] = ListItr_Begin(testlist);
	z[1] = ListItr_Set(z[0], z[2]);
	z[1] = ListItr_Get(z[0]);

	PrintRes(4 == *(int*)z[1]);
	printf("IsSetVal\n");
    ListDestroy(&testlist, NULL);
	return;
}

void IsInsertBefore(){

	int* x[4], i;
	void* z[3]; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<4; ++i)
	{
		x[i] = malloc(sizeof(int));
		*x[i]= 10;
		ListPushHead(testlist,(void*)x[i]);
	} 
    z[2]  = &i;
	z[0] = ListItr_Begin(testlist);
	z[1] = ListItr_InsertBefore(z[0], z[2]);
	z[2] = ListItr_Get(z[1]);

	PrintRes(4 == *(int*)z[2]);
	printf("IsInsetBefore\n");
    ListDestroy(&testlist, NULL);
	return;
}

void IsRemove(){

	int* x[4], i;
	void* z[2]; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<4; ++i)
	{
		x[i] = malloc(sizeof(int));
		*x[i]= 10;
		ListPushHead(testlist,(void*)x[i]);
	} 
	z[0] = ListItr_Begin(testlist);
	z[1] = ListItr_Remove(z[0]);

	PrintRes(10 == *(int*)z[1]);
	printf("IsRemove\n");
    ListDestroy(&testlist, NULL);
	return;
}

/*******************list functions tests****************/

void IsFindFirst(){

	int* x[4], i;
	void* z[3]; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<4; ++i)
	{
		x[i] = malloc(sizeof(int));
		*x[i]= i;
		ListPushHead(testlist,(void*)x[i]);
	} 
    
    z[0] = ListItr_Begin(testlist);
    z[1] = ListItr_End(testlist);
    z[1] = ListItr_Prev(z[1]);
    PrintRes(z[1] == ListItr_FindFirst(z[0], z[1], Match, (void*)x[0]));
	printf("IsFindFirstMatch\n");
    ListDestroy(&testlist, NULL);
	return;
}

void IsReturnNotFindFirst(){

	int* x[4], i;
	void* z[2]; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<4; ++i)
	{
		x[i] = malloc(sizeof(int));
		*x[i]= i;
		ListPushHead(testlist,(void*)x[i]);
	} 
    *x[0] = 10;
    z[0] = ListItr_Begin(testlist);
    z[1] = ListItr_End(testlist);
    z[1] = ListItr_Prev(z[1]);
    PrintRes(z[1] == ListItr_FindFirst(z[0], z[1], Match, (void*)x[0]));
	printf("IsReturnNotFindFirst\n");
    ListDestroy(&testlist, NULL);
	return;
}

void FindFirstNullPredicate(){

	void* z[2]; 
	List* testlist = ListCreate();
	
    z[0] = ListItr_Begin(testlist);
    z[1] = ListItr_End(testlist);
    
    PrintRes(z[1] == ListItr_FindFirst(z[0], z[1],NULL, z[1]));
	printf("FindFirstNullPredicate\n");
    ListDestroy(&testlist, NULL);
	return;
}

void IsFindFirstNullContext(){

	void* z[2]; 
	List* testlist = ListCreate();
	
    z[0] = ListItr_Begin(testlist);
    z[1] = ListItr_End(testlist);
    
    PrintRes(z[1] == ListItr_FindFirst(z[0], z[1],Match, NULL));
	printf("FindFirstNullContext\n");
    ListDestroy(&testlist, NULL);
	return;
}

/***************************************************************************/
void IsCountIf(){

	int* x[4], i;
	void* z[3]; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<4; ++i)
	{
		x[i] = malloc(sizeof(int));
		*x[i]= 10;
		ListPushHead(testlist,(void*)x[i]);
	} 
    
    z[0] = ListItr_Begin(testlist);
    z[1] = ListItr_End(testlist);
    z[2] = x[3];
    PrintRes(4 == ListItr_CountIf(z[0], z[1], Match, z[2]));
	printf("IsCountIf\n");
    ListDestroy(&testlist, NULL);
	return;
}

void IsCountIfNotFound(){

	int* x[5], i;
	void* z[2]; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<4; ++i)
	{
		x[i] = malloc(sizeof(int));
		*x[i]= 10;
		ListPushHead(testlist,(void*)x[i]);
	} 
    
    z[0] = ListItr_Begin(testlist);
    z[1] = ListItr_End(testlist);
    *x[4] = 5; 
    PrintRes(0 == ListItr_CountIf(z[0], z[1], Match, (void*)x[4]));
	printf("IsCountIfNotFound\n");
    ListDestroy(&testlist, NULL);
	return;
}

void IsCountPredicate(){

	void* z[2]; 
	List* testlist = ListCreate();
	
    z[0] = ListItr_Begin(testlist);
    z[1] = ListItr_End(testlist);
    
    PrintRes(0 == ListItr_CountIf(z[0], z[1],NULL, z[1]));
	printf("IsCountPredicate\n");
    ListDestroy(&testlist, NULL);
	return;
}

void IsCountNullContext(){

	void* z[2]; 
	List* testlist = ListCreate();
	
    z[0] = ListItr_Begin(testlist);
    z[1] = ListItr_End(testlist);
    
    PrintRes(0 == ListItr_CountIf(z[0], z[1],Match, NULL));
	printf("IsCountNullContext\n");
    ListDestroy(&testlist, NULL);
	return;
}


void IsIncForEach(){

	int* x[4], i;
	void* z[3]; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<4; ++i)
	{
		x[i] = malloc(sizeof(int));
		*x[i]= 10;
		ListPushHead(testlist,(void*)x[i]);
	} 
    
    z[0] = ListItr_Begin(testlist);
    z[1] = ListItr_End(testlist);
    z[2] = x[3];
    PrintRes( z[1] == ListItr_ForEach(z[0], z[1], Increment, z[2]));
	printf("IsIncrementAndPrintForEach\n");
    ListDestroy(&testlist, NULL);
	return;
}

void IsForEachNullPredicate(){

	void* z[2]; 
	List* testlist = ListCreate();
	
    z[0] = ListItr_Begin(testlist);
    z[1] = ListItr_End(testlist);
    
    PrintRes(z[0] == ListItr_ForEach(z[0], z[1],NULL, z[1]));
	printf("IsForEachPredicate\n");
    ListDestroy(&testlist, NULL);
	return;
}

void IsForEachNullContext(){

	void* z[2]; 
	List* testlist = ListCreate();
	
    z[0] = ListItr_Begin(testlist);
    z[1] = ListItr_End(testlist);
    
    PrintRes(z[0] == ListItr_ForEach(z[0], z[1],Match, NULL));
	printf("IsForEachNullContext\n");
    ListDestroy(&testlist, NULL);
	return;
}

void IsForEachPutStr(){

	char* x[5];
    void* z[2];
    int i;
    
    List* testlist = ListCreate();
	for(i=0; i<4; ++i)
	{
		x[i] = malloc(sizeof(char));
		*x[i]= 'a';
		ListPushHead(testlist,(void*)x[i]);
	} 
	*x[4]= 'd';
\
    z[0] = ListItr_Begin(testlist);
    z[1] = ListItr_End(testlist);
    
    PrintRes('d' ==*(char*) ListItr_ForEach(z[0], z[1], PutStr, (void*)x[3]));
	printf("IsForEachPutStr\n");
    ListDestroy(&testlist, NULL);
	return;
}

void IsSortInt(){

	int* x[300], i;
	void* z[2]; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<300; ++i)
	{
		x[i] = malloc(sizeof(int));;
	}
	for (i = 0; i < 300; i += 1)
	{
	    *x[i] = rand()%300;
	}

    for(i=0; i<300; ++i)
	{
		ListPushHead(testlist,(void*)x[i]);
	}
    
    z[0] = ListItr_Begin(testlist);
    z[1] = ListItr_End(testlist);
    
    PrintRes(1);
    ListItr_Sort(z[0], z[1], CompareIntS);
	printf("IsSort\n");
	ListItr_ForEach(z[0], z[1], PrinItems, NULL);
	printf("\n");
    ListDestroy(&testlist, NULL);
	return;
}

void IsSortChar(){

	char* x[5];
	int i;
	void* z[2]; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<5; ++i)
	{
		x[i] = malloc(sizeof(int));;
	} 
    *x[0] = 'c';
    *x[1] = 't';
    *x[2] = 'l';
    *x[3] = 'f';
    *x[4] = 'w';
    for(i=0; i<5; ++i)
	{
		ListPushHead(testlist,(void*)x[i]);
	}
    
    z[0] = ListItr_Begin(testlist);
    z[1] = ListItr_End(testlist);
    
    PrintRes(1);
    ListItr_Sort(z[0], z[1], CompareCharS);
	printf("IsSort Chars\n");
	ListItr_ForEach(z[0], z[1], PrinCharItems, NULL);
	printf("\n");
    ListDestroy(&testlist, NULL);
	return;
}

void IsSplice(){

    int* x[5], i;
	void* z[3]; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<5; ++i)
	{
		x[i] = malloc(sizeof(int));
		*x[i] = i;
		ListPushHead(testlist,(void*)x[i]);
	} 
	
    z[0] = ListItr_Begin(testlist);
    z[1] = ListItr_End(testlist);
    PrintRes(z[2] == ListItr_Splice(z[2], z[0], z[1]));
	printf("IsSplice\n");
    ListDestroy(&testlist, NULL);

}

void IsSpliceBeginEqaulDest(){

    int* x[5], i;
	void* z[2]; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<5; ++i)
	{
		x[i] = malloc(sizeof(int));
		*x[i] = i;
		ListPushHead(testlist,(void*)x[i]);
	} 
	
    z[0] = ListItr_Begin(testlist);
    z[1] = ListItr_End(testlist);
    PrintRes(z[0] == ListItr_Splice(z[0], z[0], z[1]));
	printf("IsSpliceBeginEqaulDest\n");
    ListDestroy(&testlist, NULL);

}

void IsCut(){

    int* x[5], i;
	void* z[2]; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<5; ++i)
	{
		x[i] = malloc(sizeof(int));
		*x[i] = i;
		ListPushHead(testlist,(void*)x[i]);
	} 
	
    z[0] = ListItr_Begin(testlist);
    z[1] = ListItr_End(testlist);
    ListItr_Cut(z[0], z[1]);
    
    PrintRes(ListCountItems(testlist));
	printf("IsCut\n");
    ListDestroy(&testlist, NULL);
    return;
}

void IsCutSameItter(){

	void* z[2]; 
	
	List* testlist = ListCreate();
	List* comparelist = ListCreate();
	
    z[0] = ListItr_Begin(testlist);
    z[1] = ListItr_End(testlist);
    comparelist = ListItr_Cut(z[0], z[1]);
    
    PrintRes(ListCountItems(comparelist));
	printf("IsCutSameItter\n");
    ListDestroy(&testlist, NULL);
    return;
}


void IsMerge(){

    int* x[10], i;
	void* z[5]; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<10; ++i)
	{
		x[i] = malloc(sizeof(int));
	}
	*x[0] = 12 ;
	ListPushHead(testlist,(void*)x[0]);
	z[0] = ListItr_Begin(testlist);
	*x[1] = 1 ;
	ListPushHead(testlist,(void*)x[1]);
	z[1] = ListItr_Begin(testlist);
	*x[2] = 45 ;
	ListPushHead(testlist,(void*)x[2]);
	*x[3] = 9 ;
	ListPushHead(testlist,(void*)x[3]);
	*x[4] = 79 ;
	ListPushHead(testlist,(void*)x[4]);
	z[2] = ListItr_Begin(testlist);
	*x[5] = 10 ;
	ListPushHead(testlist,(void*)x[5]);
	z[3] = ListItr_Begin(testlist);
	*x[6] = 8 ;
	ListPushHead(testlist,(void*)x[6]);
	*x[7] = 23 ;
	ListPushHead(testlist,(void*)x[7]);
	*x[8] = 73 ;
	ListPushHead(testlist,(void*)x[8]);
	z[4] = ListItr_Begin(testlist);
	
    ListItr_Merge(z[0], z[4], z[3], z[2], z[1], CompareIntS);
    z[0] = ListItr_Begin(testlist);
    z[4] = ListItr_End(testlist);
    PrintRes(1);
	printf("IsMerge\n");
	ListItr_ForEach(z[0], z[4], PrinItems, NULL);
	printf("\n");
    ListDestroy(&testlist, NULL);
	return;
}

void IsMergeWithNoSort(){

    int* x[10], i;
	void* z[5]; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<10; ++i)
	{
		x[i] = malloc(sizeof(int));
	}
	*x[0] = 12 ;
	ListPushHead(testlist,(void*)x[0]);
	z[0] = ListItr_Begin(testlist);
	*x[1] = 1 ;
	ListPushHead(testlist,(void*)x[1]);
	z[1] = ListItr_Begin(testlist);
	*x[2] = 45 ;
	ListPushHead(testlist,(void*)x[2]);
	*x[3] = 9 ;
	ListPushHead(testlist,(void*)x[3]);
	*x[4] = 79 ;
	ListPushHead(testlist,(void*)x[4]);
	z[2] = ListItr_Begin(testlist);
	*x[5] = 10 ;
	ListPushHead(testlist,(void*)x[5]);
	z[3] = ListItr_Begin(testlist);
	*x[6] = 8 ;
	ListPushHead(testlist,(void*)x[6]);
	*x[7] = 23 ;
	ListPushHead(testlist,(void*)x[7]);
	*x[8] = 73 ;
	ListPushHead(testlist,(void*)x[8]);
	z[4] = ListItr_Begin(testlist);
	
    ListItr_Merge(z[0], z[4], z[3], z[2], z[1], NULL);
    z[0] = ListItr_Begin(testlist);
    z[4] = ListItr_End(testlist);
    PrintRes(1);
	printf("IsMergeWithNoSort\n");
	ListItr_ForEach(z[0], z[4], PrinItems, NULL);
	printf("\n");
    ListDestroy(&testlist, NULL);
	return;
}

void IsUnique(){

    int* x[10], i;
	void* z[2]; 
	
	List* testlist = ListCreate();
	List* duplist = ListCreate();
	
	for(i=0; i<10; ++i)
	{
		x[i] = malloc(sizeof(int));
	}
	*x[0] = 1 ;
	ListPushHead(testlist,(void*)x[0]);
	z[0] = ListItr_Begin(testlist);
	*x[1] = 10 ;
	ListPushHead(testlist,(void*)x[1]);
	*x[2] = 13 ;
	ListPushHead(testlist,(void*)x[2]);
	*x[3] = 13 ;
	ListPushHead(testlist,(void*)x[3]);
	*x[4] = 23 ;
	ListPushHead(testlist,(void*)x[4]);
	*x[5] = 23;
	ListPushHead(testlist,(void*)x[5]);
	*x[6] = 45 ;
	ListPushHead(testlist,(void*)x[6]);
	*x[7] = 45 ;
	ListPushHead(testlist,(void*)x[7]);
	*x[8] = 78;
	ListPushHead(testlist,(void*)x[8]);
	
    PrintRes(1);
	printf("IsUnique\n");
	z[0] = ListItr_Begin(testlist);
    z[1] = ListItr_End(testlist);
    printf("the list:\n");
	ListItr_ForEach(z[0], z[1], PrinItems, NULL);
	
    duplist = ListItr_Unique(z[0], z[1], IsEqual);
    z[0] = ListItr_Begin(duplist);
    z[1] = ListItr_End(duplist);
    printf("the duplicates:\n");
	ListItr_ForEach(z[0], z[1], PrinItems, NULL);
	printf("\n");
    ListDestroy(&testlist, NULL);
	return;
}

void IsUniqueNoDuplicate(){

    int* x[4], i;
	void* z[2]; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<4; ++i)
	{
		x[i] = malloc(sizeof(int));
	}
	*x[0] = 1 ;
	ListPushHead(testlist,(void*)x[0]);
	z[1] = ListItr_Begin(testlist);
	*x[1] = 10 ;
	ListPushHead(testlist,(void*)x[1]);
	*x[2] = 11 ;
	ListPushHead(testlist,(void*)x[2]);
	*x[3] = 13 ;
    ListPushHead(testlist,(void*)x[3]);
    z[0] = ListItr_Begin(testlist);
	
    PrintRes(NULL == ListItr_Unique(z[0], z[1], IsEqual));
	printf("Is Unique No Duplicates\n");
    ListDestroy(&testlist, NULL);
	return;
}

void IsUniqueNullPredicate(){

	void* z[2]; 
	List* testlist = ListCreate();
	
    z[0] = ListItr_Begin(testlist);
    z[1] = ListItr_End(testlist);
    
    PrintRes(NULL == ListItr_Unique(z[0], z[1], NULL));
	printf("IsUniqueNULLPredicate\n");
    ListDestroy(&testlist, NULL);
	return;
}

int main(){
/*
	printf("\nist_itr.h API tests\n");
	IsListIterBegin();
	IsListIterBeginNULL();
	
	IsListIterEnd();
	IsListIterEndNULL();
	
	IsGetEqual();
	IsGetNotEqual();
	
	IsGetNext();
	IsGetNextTail();
	
	IsGetPrev();
	IsGetPrevHead();
	
	IsGetVal();
	IsGetValTail();
	IsGetValHead();
	
	IsSetVal();
	
	IsInsertBefore();
	
	IsRemove();
	
	printf("\nlist functions tests\n");
	
	IsFindFirst();
	IsReturnNotFindFirst();
	FindFirstNullPredicate();
	IsFindFirstNullContext();
	
	IsCountIf();
	IsCountIfNotFound();
	IsCountPredicate();
	IsCountNullContext();
	
	IsIncForEach();
	IsForEachNullPredicate();
	IsForEachNullContext();
	IsForEachPutStr();
*/	
	IsSortInt();
	IsSortChar();
/*	
	IsSplice();
	IsSpliceBeginEqaulDest();
	
	IsCut();
	IsCutSameItter();
	
	IsMerge();
	IsMergeWithNoSort();
	
	IsUnique();
	IsUniqueNoDuplicate();
	IsUniqueNullPredicate();
	
*/	
	return 0;
	
}


