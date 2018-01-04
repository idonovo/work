#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

# define NORMAL 5
# define NOSIZE 0
# define ITEM 10
dfgdfg
void QueueCreateTest();
void TestCreatWith0Size();

void TestIfInsert();
void TestAddBeyondSize();
void InsertAfterLastElemant();

void RemoveUnderSize();
void TestRemoveNULLQueue();
void TestRemoveNULLptr();

void TestIsEmptyAfterCreate();
void TestIsEmptyAfterInsert();
void TestIsEmptyNULLQueue();
void TestIsEmptyAfterInsertAndRemove();
void TestIsEmptyNULLQueue();

void MultipuleInsertAndRemove();

int main(){

	QueueCreateTest();
	TestCreatWith0Size();
	TestIfInsert();
	TestAddBeyondSize();
	InsertAfterLastElemant();
	RemoveUnderSize();
	TestRemoveNULLQueue();
	TestRemoveNULLptr();
	TestIsEmptyAfterCreate();
	TestIsEmptyAfterInsert();
	TestIsEmptyNULLQueue();
	TestIsEmptyAfterInsertAndRemove();

	return 0;
}

void QueueCreateTest(){
	
	Queue* testQueue;
	
	testQueue = QueueCreate(NORMAL);
	
	if(testQueue== NULL)
	{
		printf("FAIL");
	}
	else
	{	
		printf("PASS");	
	}
	printf("  TestQueueCreat\n");
	QueueDestroy(testQueue);
	return;	
}

void TestCreatWith0Size(){

	Queue* testQueue;
	testQueue = QueueCreate(NOSIZE);
	
	if(testQueue != NULL)
	{
		printf("FAIL");
	}
	else
	{	
		printf("PASS");	
	}
	printf("  Test Creat With 0 Size\n");
	QueueDestroy(testQueue);
	return;		
	
}


void TestIfInsert(){

	Queue* testQueue;
	testQueue = QueueCreate(NORMAL);

	if(QueueInsert(testQueue, ITEM) != ERR_OK){
		printf("FAIL");
	}
	else
	{	
	printf("PASS");
	}
	printf("   Test If Insert\n");	
	QueueDestroy(testQueue);
	return;	
}

	
void TestAddBeyondSize(){
	
	int i;
	Queue* testQueue;
	testQueue = QueueCreate(NORMAL);
	
	for(i=0; i<NORMAL; i++){	
		QueueInsert(testQueue, ITEM);
	}
	QueueInsert(testQueue, ITEM);
	
	if(QueueInsert(testQueue, ITEM) == ERR_OK){
		printf("FAIL");
	}
	else
	{	
		printf("PASS");
	}

	printf("   Test Add Beyond Size\n");	
	QueueDestroy(testQueue);
	return;		
			
}

void TestAddNULLQueue(){
	
	Queue* testQueue = NULL;
	
	if(QueueInsert(testQueue, ITEM) != ERR_NOT_INITIALIZED ){
		printf("FAIL");
	}
	else
	{	
		printf("PASS");
	}

	printf("   Test Add NULL Queue\n");	
	QueueDestroy(testQueue);
	return;		
			
}

void InsertAfterLastElemant(){
	
	int i;
	Queue* testQueue;
	testQueue = QueueCreate(NORMAL);
	
	for(i=0; i<NORMAL; i++){	
		QueueInsert(testQueue, ITEM);
	}
	
	if(QueueInsert(testQueue, ITEM) == ERR_OK){
		printf("FAIL");
	}
	else
	{	
		printf("PASS");
	}

	printf("   Test Insert After Last Elemant\n");
		
	QueueDestroy(testQueue);
	return;		

}

void RemoveUnderSize(){

	int i, item;
	Queue* testQueue;
	testQueue = QueueCreate(NORMAL);
	
	for(i=0; i<NORMAL; i++){	
		QueueInsert(testQueue, ITEM);
	}
	
	for(i=0; i<NORMAL; i++){	
		QueueRemove(testQueue, &item);
	}
	
	if(QueueRemove(testQueue, &item) != ERR_UNDERFLOW){
		printf("FAIL");
	}
	else
	{	
		printf("PASS");
	}

	printf("   Remove Under Size\n");
		
	QueueDestroy(testQueue);
	return;		
}

void TestRemoveNULLQueue(){
	
	int item;
	Queue* testQueue = NULL;
	
	if(QueueRemove(testQueue, &item) != ERR_NOT_INITIALIZED ){
		printf("FAIL");
	}
	else
	{	
		printf("PASS");
	}

	printf("   Test Remove NULL Queue\n");	
	QueueDestroy(testQueue);
	return;					
}

void TestRemoveNULLptr(){
	
	int* item= NULL;
	Queue* testQueue;
	testQueue = QueueCreate(NORMAL);
	
	if(QueueRemove(testQueue, item) != ERR_NOT_INITIALIZED ){
		printf("FAIL");
	}
	else
	{	
		printf("PASS");
	}

	printf("   Test Remove NULL Ptr\n");	
	QueueDestroy(testQueue);
	return;		
			
}

void TestIsEmptyAfterCreate(){
	
	Queue* testQueue;
	testQueue = QueueCreate(NORMAL);
	
	if(QueueIsEmpty(testQueue) != 0)
	{
		printf("FAIL");
	}
	else
	{	
		printf("PASS");	
	}
	printf("  Test Is Empty After Create\n");
	QueueDestroy(testQueue);
	return;	

}

void TestIsEmptyAfterInsert(){
	
	Queue* testQueue;
	testQueue = QueueCreate(NORMAL);
	QueueInsert(testQueue, ITEM);
	
	if(QueueIsEmpty(testQueue) == 0)
	{
		printf("FAIL");
	}
	else
	{	
		printf("PASS");	
	}
	printf("  Test Is Empty After Insert\n");
	QueueDestroy(testQueue);
	return;	

}

void TestIsEmptyAfterInsertAndRemove(){
	
	int i, item;
	Queue* testQueue;
	testQueue = QueueCreate(NORMAL);
	
	for(i=0; i<NORMAL; i++){	
		QueueInsert(testQueue, ITEM);
	}
	
	for(i=0; i<NORMAL; i++){	
		QueueRemove(testQueue, &item);
	}
	
	if(QueueIsEmpty(testQueue) != 0)
	{
		printf("FAIL");
	}
	else
	{	
		printf("PASS");	
	}
	printf("  Test Is Empty After Insert And Remove\n");
	QueueDestroy(testQueue);
	return;	

}

void TestIsEmptyNULLQueue(){
	
	int item;
	Queue* testQueue = NULL;
	
	if(QueueIsEmpty(testQueue) != 0)
	{
		printf("FAIL");
	}
	else
	{	
		printf("PASS");	
	}
	printf("  Test Is Empty NULL Queue\n");
	QueueDestroy(testQueue);
	return;	
				
}

void MultipuleInsertAndRemove(){
	
	int i, item;
	Queue* testQueue;
	testQueue = QueueCreate(NORMAL);
	
	for(i=0; i<2*NORMAL; i++){	
		QueueInsert(testQueue, ITEM);
	}
	
	for(i=0; i<NORMAL; i++){	
		QueueRemove(testQueue, &item);
	}
	
	for(i=0; i<2*NORMAL; i++){	
		QueueInsert(testQueue, ITEM);
	}
	
	for(i=0; i<3*NORMAL; i++){	
		QueueRemove(testQueue, &item);
	}
	
	if(QueueIsEmpty(testQueue) != 0)
	{
		printf("FAIL");
	}
	else
	{	
		printf("PASS");	
	}
	printf("  Test Is Empty After Multiple Insert And Remove\n");
	QueueDestroy(testQueue);
	return;	
}







