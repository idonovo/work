#include <stdio.h>
#include <stdlib.h>
#include "double.h"

#define SIZE 10




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


/************************************************/
void PrintRes(size_t flag);

void IsCreate();

void IsPushHead();
void IsPushHeadAfterPushHead();
void IsPushHeadChar();
void IsPushHeadNullList();

void IsPushTail();
void IsPushTailAfterPushTail();
void IsPushTailChar();
void IsPushTailNullList();

void IsPopHead();
void IsPopHeadChar();
void IsPopHeadNullList();


void IsPopTail();
void IsPopTailNullList();
void IsPopTailChar();


void IsCountItems();
void IsCountEmptyList();

void IsReturnListNotEmpty();
void IsReturnListEmpty();

void IsFindFirstEvenInt();
void IsFindFirstEvenIntBackword();

void IsDestroy();

void IsForEachAssignVal();
void IsForEachAssignStr();

/****************UserActionFunc/PredicateFunc**************/

int main(){

	IsCreate();

    IsDestroy();
    
	IsPushHead();
	IsPushHeadAfterPushHead();
	IsPushHeadNullList();
	IsPushHeadChar();
	
	IsPushTail();
	IsPushTailAfterPushTail();
	IsPushTailChar();
	IsPushTailNullList();
	
	IsPopHead();
	IsPopHeadNullList();
	IsPopHeadChar();
	
	IsPopTail();
	IsPopTailNullList();
	IsPopTailChar();
	
	IsCountItems();
	IsCountEmptyList();
	
	IsReturnListNotEmpty();
	IsReturnListEmpty();
	
	IsFindFirstEvenInt();
	
	IsFindFirstEvenIntBackword();	
	
	IsForEachAssignVal();
	/*IsForEachAssignStr();*/

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

/* *********ListCreateTests****************/

void IsCreate(){

	List* testlist = ListCreate();
    PrintRes(testlist != NULL);
    printf("Is create test\n");
    ListDestroy(&testlist, NULL);
    return;
}

/****************ListPushHeadTests*****************/

void IsPushHead(){
	
	int* x;
	List* testlist = ListCreate();
	x =  malloc(sizeof(int));
	*x = 10; 
	
	PrintRes(ListPushHead(testlist,(void*)x) == LIST_OK);
	printf("Is Push Head test\n");
    ListDestroy(&testlist, _destoryFunc);
    return;
}

void IsPushHeadAfterPushHead(){
	
	int* x;
	int* y;
	List* testlist = ListCreate();
	x =  malloc(sizeof(int));
	y =  malloc(sizeof(int));
	*x = 10; 
	*y = 12;
	
	ListPushHead(testlist,(void*)y);
	PrintRes(ListPushHead(testlist,(void*)x) == LIST_OK);
	printf("Is Push Head After Push Head test\n");
    ListDestroy(&testlist,_destoryFunc);
    return;
}

void IsPushHeadChar(){
	
	char* x;
	List* testlist = ListCreate();
	x =  malloc(sizeof(int));
	*x = 'a'; 
	
	PrintRes(ListPushHead(testlist,(void*)x) == LIST_OK);
	printf("Is Push Head Char test\n");
    ListDestroy(&testlist,_destoryFunc);
    return;
}

void IsPushHeadNullList(){

    PrintRes(ListPushHead(NULL, NULL) == LIST_UNINITIALIZED);
	printf("Is Push NULL list\n");
    return;
}
/***************ListPushTailTests*****************/

void IsPushTail(){
	
	int* x;
	List* testlist = ListCreate();
	x =  malloc(sizeof(int));
	*x = 10; 
	
	PrintRes(ListPushTail(testlist,(void*)x) == LIST_OK);
	printf("Is Push Tail test\n");
    ListDestroy(&testlist,_destoryFunc);
    return;
}

void IsPushTailChar(){
	
	char* x;
	List* testlist = ListCreate();
	x =  malloc(sizeof(int));
	*x = 'a'; 
	
	PrintRes(ListPushTail(testlist,(void*)x) == LIST_OK);
	printf("Is Push Tail Char test\n");
    ListDestroy(&testlist,_destoryFunc);
    return;
}


void IsPushTailAfterPushTail(){
	
	int* x;
	int* y;
	List* testlist = ListCreate();
	x =  malloc(sizeof(int));
	y =  malloc(sizeof(int));
	*x = 10; 
	*y = 12;
	
	ListPushHead(testlist,(void*)y);
	PrintRes(ListPushTail(testlist,(int*)x) == LIST_OK);
	printf("Is Push Tail After Push Tail test\n");
    ListDestroy(&testlist,_destoryFunc);
    return;
}

void IsPushTailNullList(){

    PrintRes(ListPushTail(NULL, NULL) == LIST_UNINITIALIZED);
	printf("Is Push NULL list\n");
    return;
}
/************ListPopHead tests_**************/

void IsPopHead(){

	int* x;
	int* y;
	void* a;
	List* testlist = ListCreate();
	x =  malloc(sizeof(int));
	y =  malloc(sizeof(int));
	*x = 10; 
	*y = 12;
	a = NULL;
	
	ListPushHead(testlist,(void*)y);
	ListPushHead(testlist,(void*)x);
	
	PrintRes(ListPopHead(testlist,&a) == LIST_OK);
	printf("Is Pop Head \n");
    ListDestroy(&testlist,_destoryFunc);
    return;
}

void IsPopHeadChar(){

	char* x;
	char* y;
	void* a;
	List* testlist = ListCreate();
	x =  malloc(sizeof(int));
	y =  malloc(sizeof(int));
	*x = 'a'; 
	*y = 'b';
	a = NULL;
	
	ListPushHead(testlist,(void*)y);
	ListPushHead(testlist,(void*)x);
	
	PrintRes(ListPopHead(testlist,&a) == LIST_OK);
	printf("Is Pop Head Char\n");
    ListDestroy(&testlist,_destoryFunc);
    return;
}

void IsPopHeadNullList(){

    PrintRes(ListPopHead(NULL, NULL) == LIST_UNINITIALIZED);
	printf("Is Push NULL list\n");
    return;
}
/*******************ListPopTail Tests**************/
void IsPopTail(){

	int* x;
	int* y;
	void* a;
	List* testlist = ListCreate();
	x =  malloc(sizeof(int));
	y =  malloc(sizeof(int));
	*x = 10; 
	*y = 12;
	a = NULL;
	
	ListPushHead(testlist,(void*)y);
	ListPushHead(testlist,(void*)x);
	
	PrintRes(ListPopTail(testlist,&a) == LIST_OK);
	printf("Is Pop Tail \n");
    ListDestroy(&testlist,_destoryFunc);
    return;
}

void IsPopTailChar(){
	char* x;
	char* y;
	void* a;
	List* testlist = ListCreate();
	x =  malloc(sizeof(int));
	y =  malloc(sizeof(int));
	*x = 'a'; 
	*y = 'b';
	a = NULL;
	
	ListPushHead(testlist,(void*)y);
	ListPushHead(testlist,(void*)x);
	
	PrintRes(ListPopTail(testlist,&a) == LIST_OK);
	printf("Is Pop Tail Char\n");
    ListDestroy(&testlist,_destoryFunc);
    return;
}

void IsPopTailNullList(){

    PrintRes(ListPopTail(NULL, NULL) == LIST_UNINITIALIZED);
	printf("Is Push NULL list\n");
    return;
}
/* ****************ListCountItem tests****************/
void IsCountItems(){

	int* x;
	int* y;
	
	List* testlist = ListCreate();
	
	y = malloc(sizeof(int));
	x = malloc(sizeof(int));
	*x = 10; 
	*y = 12;
	
	ListPushHead(testlist,(void*)y);
	ListPushHead(testlist,(void*)x);
	
	PrintRes(ListCountItems(testlist) == 2);
	printf("Is count items \n");
    ListDestroy(&testlist,_destoryFunc);
    return;

}

void IsCountEmptyList(){

	List* testlist = ListCreate();
	
	PrintRes(ListCountItems(testlist) == 0);
	printf("Is count items empty list \n");
    ListDestroy(&testlist, NULL);
    return;
}

/* ****************ListIsEmpty tests****************/
void IsReturnListNotEmpty(){

	int* x;
	int* y;
	
	List* testlist = ListCreate();
	
	y = malloc(sizeof(int));
	x = malloc(sizeof(int));
	*y=8;
	*x=8;
	
	ListPushHead(testlist,(void*)y);
	ListPushHead(testlist,(void*)x);
	
	PrintRes(ListIsEmpty(testlist) == 0);
	printf("Is Return List Not Empty \n");
    ListDestroy(&testlist,_destoryFunc);
    return;

}

void IsReturnListEmpty(){

	List* testlist = ListCreate();
	
	PrintRes(ListIsEmpty(testlist) == 1);
	printf("Is Return List Empty \n");
    ListDestroy(&testlist, NULL);
    return;
}

/****************UserActionFunc/PredicateFunc**************/

/*********************FindFirstForward tests***************************/
void IsFindFirstEvenInt(){

	int* x[6], i;
	int* a;
	void* z = NULL; 
	
	List* testlist = ListCreate();
	
	x[0] =  malloc(sizeof(int));
	*x[0] = 2;
	ListPushHead(testlist,(void*)x[0]);
	a =  malloc(sizeof(int));
	*a =2;
	
	for(i=1; i<6; i++)
	{
		x[i] = malloc(sizeof(int));
		*x[i] = 5;
		ListPushHead(testlist,(void*)x[i]);
	}

	FindFirstForward(testlist, FindEven, (void*)a, &z);
	PrintRes(*(int*)z == 2);
	printf("Is Find First Even Int\n");
    ListDestroy(&testlist,_destoryFunc);
    return;

}

/*********************FindFirstBackward tests***************************/
void IsFindFirstEvenIntBackword(){

	int* x[6], i;
	int* a;
	void* z = NULL; 
	
	List* testlist = ListCreate();
	
	
	a =  malloc(sizeof(int));
	*a =2;
	
	for(i=0; i<5; i++)
	{
		x[i] = malloc(sizeof(int));
		*x[i] = 5;
		ListPushHead(testlist,(void*)x[i]);
	}
	x[0] =  malloc(sizeof(int));
	*x[0] = 2;
	ListPushHead(testlist,(void*)x[0]);
	
	FindFirstBackward(testlist, FindEven, (void*)a, &z);
	PrintRes(z != NULL);
	printf("IsFindFirstEvenIntBackword\n");
    ListDestroy(&testlist, _destoryFunc);
    return;

}

/****************Destroy tests************************/
void IsDestroy(){

	int* x[5], i;

	List* testlist = ListCreate();
	for(i=0; i<5; i++)
	{
		x[i] = malloc(sizeof(int));
		*x[i] = i;
		ListPushHead(testlist,(void*)x[i]);
	}
	ListDestroy(&testlist,_destoryFunc);
	printf("PASS   :Is Destroy\n");
    return;
}

/*********************FindFirstBackward tests***************************/
void IsForEachAssignVal(){

	size_t i;
	int* x[6];
	int c =10;
	int* d =&c; 
	
	List* testlist = ListCreate();
	
	for(i=0; i<6; i++)
	{
		x[i] = malloc(sizeof(int));
		*x[i] = 23;
		ListPushHead(testlist,(void*)x[i]);
	}

	i = ListForEach(testlist, Assign, (void*)d);
	PrintRes(i == 6);
	printf("%d", *d);
	printf("Is For Each Assign Val\n");
    ListDestroy(&testlist, _destoryFunc);
    return;

}

/*
void IsForEachAssignStr(){

	size_t i;
	char* x[6]= NULL;
	List* testlist = ListCreate();
	
	for(i=0; i<6; i++)
	{
		x[i] = malloc(sizeof(char*));
		ListPushHead(testlist,(void*)x[i]);
	}

	i = ListForEach(testlist, AssignStr, "IDO");
	PrintRes(i == 6);
	printf("Is For Each Assign Str\n");
    ListDestroy(&testlist,(PredicateFunc*)_destoryFunc);
    return;

}
*/

