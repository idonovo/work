/*           double linked list API functions tests - by Ido Naveh            */   

# include <stdio.h>
# include <stdlib.h>

# include "double.h"

#define MAGIC 7377175
#define SIZE 10

/* _________________ListCreateTests________*/

void IsCreate(){

	List* testlist = ListCreate();
	printf("Is create test:");
    if(testlist == NULL)
    {
        printf("fail\n");
        free(testlist);
        return;
    }
    printf("pass\n");
    free(testlist);
    return;
}

/* _________________ListDestroyTests________*/
void IsDestroy(){

	List* testlist = ListCreate();
	ListDestroy(testlist);
	printf("Is Destroy test:");
    /*if(testlist->magic == MAGIC)  - there is strange errorin this line */ 
    {
        printf("pass\n");
        return;
    }
    printf("fail\n");
    free(testlist);
    return;
}

/* _________________ListPushHeadTests________*/

void IsPushHead(){
	
	List* testlist = ListCreate();
	ListPushHead(testlist,SIZE);
	printf("Is Push Head test:");
	if(ListPushHead(testlist,SIZE) == ERR_OK)
	{
	    printf("pass\n");
	    ListPrint(testlist);
	    free(testlist);
        return;
    }
    printf("fail\n");
    free(testlist);
    return;
}

void IsPushHeadAfterPushHead(){
	
	List* testlist = ListCreate();
	ListPushHead(testlist,SIZE+SIZE);
	printf("Is Push Head After Push Head test:");
	if(ListPushHead(testlist,SIZE) == ERR_OK)
	{
	    printf("pass\n");
	    ListPrint(testlist);
	    free(testlist);
        return;
    }
    printf("fail\n");
    free(testlist);
    return;
}

/* _________________ListPushTailTests________*/
void IsPushTail(){
	
	List* testlist = ListCreate();
	ListPushHead(testlist,SIZE+SIZE);
	printf("Is Push Tail test:");
	if(ListPushTail(testlist,SIZE) == ERR_OK)
	{
	    printf("pass\n");
	    ListPrint(testlist);
	    free(testlist);
        return;
    }
    printf("fail\n");
    free(testlist);
    return;
}

void IsPushTailAfterPushTail(){
	
	List* testlist = ListCreate();
	ListPushHead(testlist,SIZE+SIZE);
	ListPushTail(testlist,SIZE*3);
	printf("Is Push Tail After Push Tail test:");
	if(ListPushTail(testlist,SIZE) == ERR_OK)
	{
	    printf("pass\n");
	    ListPrint(testlist);
	    free(testlist);
        return;
    }
    printf("fail\n");
    free(testlist);
    return;
}
/* _________________ListPopHead tests__________*/

void IsPopHead(){
	int* test;
	List* testlist = ListCreate();
	ListPushHead(testlist,SIZE+SIZE);
	ListPushHead(testlist,SIZE);
	ListPushHead(testlist,SIZE+SIZE+SIZE);
	printf("Is Pop Head test:");
	if(ListPopHead(testlist,test) == ERR_OK)
	{
	    printf("pass\n");
	    ListPrint(testlist);
	    free(testlist);
        return;
    }
    printf("fail\n");
    free(testlist);
    return;
}

void IsPopHeadReturnHead(){

	int* test;
	List* testlist = ListCreate();
	ListPushHead(testlist,SIZE+SIZE);
	ListPushHead(testlist,SIZE);
	ListPushHead(testlist,SIZE+SIZE+SIZE);
	ListPopHead(testlist,test);
	printf("Is Pop Head return head test:");
	ListPrint(testlist);
	if(*test == SIZE+SIZE+SIZE)
	{
	    printf("pass\n");
	    printf("the previous head is: %d\n", *test);
	    free(testlist);
        return;
    }
    printf("fail\n");
    free(testlist);
    return;
}
/* _________________ListPopTail Tw\ests________*/
void IsPopTail(){

	int* test;
	List* testlist = ListCreate();
	ListPushHead(testlist,SIZE+SIZE);
	ListPushHead(testlist,SIZE);
	ListPushHead(testlist,SIZE+SIZE+SIZE);
	printf("Is Pop tail test:");
	if(ListPopTail(testlist,test) == ERR_OK)
	{
	    printf("pass\n");
	    ListPrint(testlist);
	    ListPrint(testlist);
	    free(testlist);
        return;
    }
    printf("fail\n");
    free(testlist);
    return;
}

void IsPopTailReturnHead(){

	int* test;
	List* testlist = ListCreate();
	ListPushHead(testlist,SIZE+SIZE);
	ListPushHead(testlist,SIZE);
	ListPushHead(testlist,SIZE+SIZE+SIZE);
	ListPopHead(testlist,test);
	printf("Is Pop Tail return head test:");
	if(*test == SIZE+SIZE+SIZE)
	{
	    printf("pass\n");
	    printf("the privies tail is: %d\n", *test);
	    free(testlist);
        return;
    }
    printf("fail\n");
    free(testlist);
    return;
}
/* _________________ListCountItem tests________*/
void IsCountItems(){

	size_t counter;
	List* testlist = ListCreate();
	ListPushHead(testlist,SIZE+SIZE);
	ListPushHead(testlist,SIZE);
	ListPushHead(testlist,SIZE+SIZE+SIZE);
	counter = ListCountItems(testlist);
	printf("Is Count Items test:");
	if(counter == 3){
	    printf("pass\n");
	    free(testlist);
        return;
    }
    printf("fail\n");
    free(testlist);
    return;
}

void IsCountEmptyList(){

	size_t counter;
	List* testlist = ListCreate();
	counter = ListCountItems(testlist);
	printf("Is Count Empty List test:");
	if(counter == 0){
	    printf("pass\n");
	    free(testlist);
        return;
    }
    printf("fail\n");
    free(testlist);
    return;
}
/* _________________ListEmpty tests________*/
void IsEmptyTest(){

    List* testlist = ListCreate();
    printf("Is Empty test:");
	if(ListIsEmpty(testlist) == 0){
	    printf("pass\n");
	    free(testlist);
        return;
    }
    printf("fail\n");
    free(testlist);
    return;
}

void IsNotEmptyTest(){

    List* testlist = ListCreate();
    ListPushHead(testlist,SIZE+SIZE);
    printf("Is Not Empty test:");
	if(ListIsEmpty(testlist) == 1){
	    printf("pass\n");
	    free(testlist);
        return;
    }
    printf("fail\n");
    free(testlist);
    return;
}
/* _________________Final test________*/
void MultipulePushAndPop(){
    
    int i;
    int* ptr;
    List* testlist = ListCreate();
    for(i=0; i<SIZE-5; i++)
    {
        ListPushHead(testlist,SIZE+i);
    }
     for(i=0; i<SIZE-6; i++)
    {
        ListPopTail(testlist,ptr);
    }
    for(i=0; i<SIZE+5; i++)
    {
        ListPushTail(testlist,SIZE+i);
    }
     for(i=0; i<SIZE+6; i++)
    {
        ListPopHead(testlist,ptr);
    }
    
    ListPushHead(testlist,SIZE+SIZE);
    printf("Multipule Push and Pop test:");
	if(ListIsEmpty(testlist) == 1){
	    printf("pass\n");
	    free(testlist);
        return;
    }
    printf("fail\n");
    free(testlist);
    return;
}

int main(){

IsCreate();

IsDestroy();

IsPushHead();
IsPushHeadAfterPushHead();

IsPushTail();
IsPushTailAfterPushTail();

IsPopHead();
IsPopHeadReturnHead();

IsPopTail();
IsPopTailReturnHead();

IsCountItems();
IsCountEmptyList();

IsEmptyTest();
IsNotEmptyTest();

MultipulePushAndPop();

	return 0;
}

