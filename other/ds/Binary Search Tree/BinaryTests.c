/*           Binary Tree API functions tests - by Ido Naveh            */   
#include <stdio.h>
#include <stdlib.h>

#include "../../inc/bin_tree.h"


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
	
	printf("%3d", *(int*)_element);

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


void IsCreate(){
	
	Tree* testTree = TreeCreate();
	printf("Is Create Test:");
	if (testTree != NULL){
		printf("PASS\n");
		free(testTree);
		return;
	}
	printf("FAIL\n");
	free(testTree);
	return;
}	

void IsInsert(){
	
	Tree* testTree = TreeCreate();
	printf("Is Insert Test:");
	if (TreeInsert(testTree, SIZE) == ERR_OK){
		printf("PASS\n");
		free(testTree);
		return;
	}
	printf("FAIL\n");
	free(testTree);
	return;
}	

void IsInsertNullTree(){
	
	Tree* testTree = NULL;
	printf("Is Insert Null Test:");
	if (TreeInsert(testTree, SIZE) == ERR_NOT_INITIALIZED){
		printf("PASS\n");
		free(testTree);
		return;
	}
	printf("FAIL\n");
	free(testTree);
	return;
}	

void IsRihgtLeftInsert(){
	
	Tree* testTree = TreeCreate();
	TreeInsert(testTree, SIZE);
	TreeInsert(testTree, SIZE+SIZE);
	printf("Is Right Left Insert Test:");
	if (TreeInsert(testTree, SIZE*3) == ERR_OK){
		printf("PASS\n");
		free(testTree);
		return;
	}
	printf("FAIL\n");
	free(testTree);
	return;
}
void IsLeftRightInsert(){
	
	Tree* testTree = TreeCreate();
	TreeInsert(testTree, SIZE*2);
	TreeInsert(testTree, SIZE*3);
	printf("Is Left Right Insert Test:");
	if (TreeInsert(testTree, SIZE) == ERR_OK){
		printf("PASS\n");
		free(testTree);
		return;
	}
	printf("FAIL\n");
	free(testTree);
	return;
}

void IsSameDataInsert(){
	
	Tree* testTree = TreeCreate();
	TreeInsert(testTree, SIZE);
	TreeInsert(testTree, SIZE+SIZE);
	printf("Is Same Data Insert Test:");
	if (TreeInsert(testTree, SIZE) == ERR_DUPLICATE_VALUE){
		printf("PASS\n");
		free(testTree);
		return;
	}
	printf("FAIL\n");
	free(testTree);
	return;
}

void IsInnerDataFound(){

    Tree* testTree = TreeCreate();
	TreeInsert(testTree, SIZE);
	TreeInsert(testTree, SIZE+SIZE);
    printf("Is Data Found Test:");
	if (TreeIsDataFound(testTree, SIZE) == 1){
		printf("PASS\n");
		free(testTree);
		return;
	}
	printf("FAIL\n");
	free(testTree);
	return;

}

void IsOuterDataFound(){

    Tree* testTree = TreeCreate();
	TreeInsert(testTree, SIZE);
	TreeInsert(testTree, SIZE+SIZE);
    printf("Is Data Not Found Test:");
	if (TreeIsDataFound(testTree, 1 + SIZE) == 0){
		printf("PASS\n");
		free(testTree);
		return;
	}
	printf("FAIL\n");
	free(testTree);
	return;

}

void IsDoubleDestroy(){

    Tree* testTree = TreeCreate();
	TreeInsert(testTree, SIZE);
    TreeDestroy(testTree);
    TreeDestroy(testTree);
    printf("Double Destroy Test: PASS\n");
    return;
}

void MultipuleInsertTest(){
    
    Tree* testTree = TreeCreate();
	TreeInsert(testTree, SIZE);
    TreeInsert(testTree, SIZE-1);
    TreeInsert(testTree, SIZE+4);
    TreeInsert(testTree, SIZE+3);
    TreeInsert(testTree, SIZE-7);
 
    printf("Multipule Insert and Print Test:");
	if (TreeInsert(testTree, SIZE+1) == ERR_OK){
		printf("PASS\n");
		printf("InOrder:");
		TreePrint(testTree, IN_ORDER);
		printf("PreOrder:");
		TreePrint(testTree, PRE_ORDER);
		printf("Post Order:");
		TreePrint(testTree, POST_ORDER);
		free(testTree);
		return;
	}
	printf("FAIL\n");
	free(testTree);
	return;

}
int main(){

IsCreate();
IsInsert();
IsInsertNullTree();
IsRihgtLeftInsert();
IsLeftRightInsert();
IsSameDataInsert();
IsInnerDataFound();
IsOuterDataFound();
IsDoubleDestroy();
MultipuleInsertTest();

	return 0;
}
