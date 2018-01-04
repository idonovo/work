/*           Binary Tree API functions tests - by Ido Naveh            */   

# include <stdio.h>
# include <stdlib.h>

# include "../../inc/bin_tree.h"


/****************UserActionFunc/PredicateFunc**************/
void _destoryFunc(void* _elemant){
	
	free(_elemant);
	
	return;
}

int Match(void* _element, void* _context){
	
	if(*(int*)_element == *(int*)_context)
	{
		return 0;
	}
	return 1;
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
	
	if(*(int*)_a > *(int*)_b)
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

/**********************************BST tests***/

void IsCreate(){

      BSTree* test = BSTree_Create(CompareIntS);
      PrintRes(NULL !=test);
      printf("IsCreat\n");
      free(test);
      return;
}
      

void IsInsert(){
     
     int* a[6];
     BSTree* test = BSTree_Create(CompareIntS);
     

    a[0] = malloc(sizeof(int));
    *a[0] = 5;
    BSTree_Insert(test, (void*)a[0]);
    a[1] = malloc(sizeof(int));
    *a[1] =3;
    BSTree_Insert(test, (void*)a[1]);
    a[2] = malloc(sizeof(int));
    *a[2] =7;
    BSTree_Insert(test, (void*)a[2]);
    a[3] = malloc(sizeof(int));
    *a[3] =4;
    BSTree_Insert(test, (void*)a[3]);
    a[4] = malloc(sizeof(int));
    *a[4] =6;
    BSTree_Insert(test, (void*)a[4]);

    a[5] = malloc(sizeof(int));
    *a[5] = 10; 
	PrintRes(NULL != BSTree_Insert(test, (void*)a[5]));
	printf("IsInert\n");
	printf("POSTORDER");
	BSTree_ForEach(test, BSTREE_TRAVERSAL_POSTORDER, PrinItems, NULL);
	printf("\n");
	printf("PREORDER");
	BSTree_ForEach(test,  BSTREE_TRAVERSAL_PREORDER, PrinItems, NULL);
	printf("\n");
	printf("INORDER");
	BSTree_ForEach(test, BSTREE_TRAVERSAL_INORDER, PrinItems, NULL);
	printf("\n");
	BSTree_Destroy(test, _destoryFunc);
    return;

}

void IsInsertNullItem(){
     
    BSTree* test = BSTree_Create(CompareIntS);
    PrintRes(NULL == BSTree_Insert(test, NULL));
    printf("IsInertNULLItem\n");
    free(test);
    return;

}

void IsInsertNullTree(){
     
    BSTree* test = BSTree_Create(CompareIntS);
    PrintRes(NULL == BSTree_Insert(NULL, NULL));
    printf("IsInertNULLTree\n");
    free(test);
    return;

}

void IsDestroy(){
     
     int* a[5] ,i;
     BSTree* test = BSTree_Create(CompareIntS);
     
     for(i=0; i<5; ++i)
     {
        a[i] = malloc(sizeof(int));
        *a[i] = i;
        BSTree_Insert(test, (void*)a[i]);
     }
    BSTree_Destroy(test, _destoryFunc);
    PrintRes(1);
    printf("IsDestory\n");
    return;

}

void IsFindFirst(){
     
     int* a[3] ,i;
     BSTreeItr tester;
     BSTree* test = BSTree_Create(CompareIntS);
     
     for(i=0; i<3; ++i)
     {
        a[i] = malloc(sizeof(int));
        *a[i] = i;
        BSTree_Insert(test, (void*)a[i]);
     }
   	tester = BSTree_FindFirst(test, Match, (void*)a[2]);
   	PrintRes(a[2] == BSTreeItr_Get(tester));
    printf("IsFindFirst\n");
    BSTree_Destroy(test, _destoryFunc);
    return;

}

void IsFindFirstNotExistVal(){
     
     int* a[3] ,i;
     BSTree* test = BSTree_Create(CompareIntS);
     
     for(i=0; i<2; ++i)
     {
        a[i] = malloc(sizeof(int));
        *a[i] = i;
        BSTree_Insert(test, (void*)a[i]);
     }
    a[2] = malloc(sizeof(int));
    *a[2] = 10;
    PrintRes(NULL == BSTree_FindFirst(test, Match, (void*)a[2]));
    printf("IsFindFirstNotExistVal\n");
    BSTree_Destroy(test, _destoryFunc);
    return;

}

void IsReturnBegin(){
     
     int* a[10] ,i;
     BSTreeItr* compare;
     BSTree* test = BSTree_Create(CompareIntS);
     
     for(i=9; i>6; --i)
     {
        a[i] = malloc(sizeof(int));
        *a[i] = i;
        BSTree_Insert(test, (void*)a[i]);
     }
     for(i=0; i<5; ++i)
     {
        a[i] = malloc(sizeof(int));
        *a[i] = i;
        BSTree_Insert(test, (void*)a[i]);
     }
    
    compare = BSTreeItr_Begin(test);
    PrintRes(BSTreeItr_Get(compare) == a[0]);
    printf("IsReturnBegin\n");
    BSTree_Destroy(test, _destoryFunc);
    return;
}

void IsReturnEnd(){

     int* a[10] ,i;
     BSTree* test = BSTree_Create(CompareIntS);
     
     for(i=9; i>6; --i)
     {
        a[i] = malloc(sizeof(int));
        *a[i] = i;
        BSTree_Insert(test, (void*)a[i]);
     }
    
    PrintRes(NULL == BSTreeItr_End(test));
    printf("IsReturnEnd\n");
    BSTree_Destroy(test, _destoryFunc);
    return;

}

void IsReturnIfEquals(){

     int* a[6] ,i;
     BSTreeItr* compare[2];
     BSTree* test = BSTree_Create(CompareIntS);
     
     for(i = 0; i < 6; ++i)
     {
        a[i] = malloc(sizeof(int));
        *a[i] = i;
        BSTree_Insert(test, (void*)a[i]);
     }
   	compare[0] = BSTree_FindFirst(test, Match, (void*)a[2]);
    compare[1] = BSTree_FindFirst(test, Match, (void*)a[2]);
    PrintRes(BSTreeItr_Equals(compare[0],compare[1]));
    printf("IsReturnIfEquals\n");
    BSTree_Destroy(test, _destoryFunc);
    return;
}

void IsReturnNotEquals(){

     int* a[6] ,i;
     BSTreeItr compare[2];
     BSTree* test = BSTree_Create(CompareIntS);
     
     for(i = 0; i < 6; ++i)
     {
        a[i] = malloc(sizeof(int));
        *a[i] = i;
        BSTree_Insert(test, (void*)a[i]);
     }
   	compare[0] = BSTree_FindFirst(test, Match, (void*)a[2]);
    compare[1] = BSTree_FindFirst(test, Match, (void*)a[4]);
    PrintRes(!BSTreeItr_Equals(compare[0],compare[1]));
    printf("IsReturnIfNotEquals\n");
    BSTree_Destroy(test, _destoryFunc);
    return;
}

void IsReturnNextChild(){ 
     
    int* a[3];
    BSTreeItr tester;
    BSTree* test = BSTree_Create(CompareIntS);
     
    a[0] = malloc(sizeof(int));
    *a[0] = 5;
    BSTree_Insert(test, (void*)a[0]);
    a[1] = malloc(sizeof(int));
    *a[1] =3;
    BSTree_Insert(test, (void*)a[1]);
    a[2] = malloc(sizeof(int));
    *a[2] =7;
    BSTree_Insert(test, (void*)a[2]);
    
   	tester = BSTree_FindFirst(test, Match, (void*)a[0]);
    PrintRes(BSTreeItr_Next(tester) == BSTree_FindFirst(test, Match, (void*)a[2]));
    printf("IsReturnNextChild\n");
    BSTree_Destroy(test, _destoryFunc);
    return;
}

void IsReturnNextParent(){ 
     
    int* a[3];
    BSTreeItr tester;
    BSTree* test = BSTree_Create(CompareIntS);
     
    a[0] = malloc(sizeof(int));
    *a[0] = 5;
    BSTree_Insert(test, (void*)a[0]);
    a[1] = malloc(sizeof(int));
    *a[1] =3;
    BSTree_Insert(test, (void*)a[1]);
    a[2] = malloc(sizeof(int));
    *a[2] =7;
    BSTree_Insert(test, (void*)a[2]);
    
   	tester = BSTree_FindFirst(test, Match, (void*)a[2]);
    PrintRes(BSTreeItr_Next(tester) == BSTree_FindFirst(test, Match, (void*)a[0]));
    printf("IsReturnNext\n");
    BSTree_Destroy(test, _destoryFunc);
    return;
}

int main(){

IsCreate();
IsInsert();
IsInsertNullItem();
IsInsertNullTree();

IsDestroy();

IsFindFirst();
IsFindFirstNotExistVal();

IsReturnBegin();
IsReturnEnd();

IsReturnIfEquals();
IsReturnNotEquals();
IsReturnNextChild();
IsReturnNextParent();


/*
IsRihgtLeftInsert();
IsLeftRightInsert();
IsSameDataInsert();
IsInnerDataFound();
IsOuterDataFound();
IsDoubleDestroy();
MultipuleInsertTest();*/

	return 0;
}
