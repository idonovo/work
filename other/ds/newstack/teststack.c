#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "stack.h"




void TestStackCreat(){
	

	Stack* testStack;
	printf("TestDoesCreat:");

	testStack = StackCreate(5, 5);
	
	if(testStack == NULL){
	
		printf("FAILURE\n");
		return;
	}	
		
	
	printf("PASSED: Stack Created\n");
	return;	
}

void TestStackCreatWith0Size(){
	
	Stack* testStack;
	printf("TestCreatWith0Size:");
	testStack = StackCreate(0, 5);
	
	if(testStack == NULL){
	
		printf("FAILURE\n");
		return;
	}	
		
	
	printf("PASSED: sTACK With Size 0 Created\n");
	return;	
}

void TestStackBlockIs0(){
	
	Stack* testStack;
	printf("Test Stack Block Is 0:");
	testStack = StackCreate(5, 0);
	
	if(testStack == NULL){
	
		printf("FAILURE\n");
		
		return;
	}	
		
	
	printf("PASSED: Stack With Block 0 Created\n");
	return;	
}


void TestStackPush(){
	
	int item = 5;
	Stack* testStack;
	printf("Test if Push Work:");
	testStack = StackCreate(5, 5);
	
	if(StackPush(testStack, item)!=ERR_OK){

		printf("FAILURE\n");
	}	
		
	
	printf("PASSED: Push Work!\n");
		
}

void PushWith0Block(){

	int item = 5;
	Stack* testStack;
	printf("Test if Push with 0 blockWork:");
	testStack = StackCreate(5, 0);
	
	if(StackPush(testStack, item) != ERR_OK){

		printf("FAILURE\n");
	}	
		
	
	printf("PASSED: Push Work!\n");
	return;	
}

void PushWithResize(){

	int i, item = 5;
	Stack* testStack;
	printf("Test if Push with Resize kWork:");
	testStack = StackCreate(3, 3);

	for(i=0;i<5; i++){

		if(StackPush(testStack, item)!=ERR_OK){
			printf("FAILURE\n");
		}	
	}
	
	printf("PASSED: Push Work!\n");
		
}

void PushWithNullStack(){
	

	int item;
	Stack* testStack = NULL;
	printf("Test Push With Null:");
	
	
	if(StackPush(testStack, item) != ERR_NOT_INITIALIZED){
			printf("FAILURE\n");
			return;
		}	
	
	printf("PASSED: Push rejects NULL Stack!\n");
	return;	
}



void TopAfterPush(){

	int item = 5;
	Stack* testStack;
	printf("Test of Top after Push:");
	testStack = StackCreate(5, 5);
	StackPush(testStack, item);

	if(StackTop(testStack, &item)!=ERR_OK){

		printf("FAILURE\n");
		return;
	}	
	

	printf("PASSED: Push Work!\n");

}

void TopWithNullPoiner(){
	
	int* item = NULL;
	Stack* testStack;
	testStack = StackCreate(5, 5);
	printf("Test Top With Null Pointer:");
	
	if(StackTop(testStack, item) != ERR_NOT_INITIALIZED){
			printf("FAILURE\n");
			return;
		}	
	
	printf("PASSED: Top rejects NULL Pointer!\n");
	return;	
}

		
void TestTStackIsEmptyWhenStackEmpty(){

	Stack* testStack;
	testStack = StackCreate(5, 5);
	printf("Test StackEmpty after Create:");
	
	
	if(StackIsEmpty(testStack) > 0){
			printf("FAILURE\n");
			return;
	}	
	
	printf("PASSED: Stack is Empty!!\n");
	return;	
}


void TestTStackIsEmptyAfterPush(){
	
	int item = 7;
	Stack* testStack;
	testStack = StackCreate(5, 5);
	printf("Test StackEmpty after Push:");
	StackPush(testStack, item);
	
	if(StackIsEmpty(testStack) == 0){
			printf("FAILURE\n");
			return;
	}	
	
	printf("PASSED: Stack is Empty!\n");
	return;	
}

void PopWithNullStack(){
	
	int item;
	Stack* testStack = NULL;
	printf("Test Pop With Null:");
	
	
	if(StackPop(testStack, &item) != ERR_NOT_INITIALIZED){
			printf("FAILURE\n");
		}	
	
	printf("PASSED: Pop rejects NULL Stack!\n");
		
}


void TestPopAfterPush(){
	
	int item = 5;
	Stack* testStack;
	printf("Test if Pop after push:");
	testStack = StackCreate(5, 5);
	StackPush(testStack, item);
	
	if(StackPop(testStack, &item) != ERR_OK){

		printf("FAILURE\n");
		return;
	}	
		
	printf("PASSED: Pop Work!\n");
	return;	
}

void TestPopAfterResize(){
	
	int i;
	int item = 5;
	Stack* testStack;
	printf("Test if Push Work after resize:");
	testStack = StackCreate(2, 2);
	StackPush(testStack, item);

	for(i=0;i<4; i++){

		StackPush(testStack,i);	
	}

	if(StackPop(testStack, &item) != ERR_OK){

		printf("FAILURE\n");
	}	
		
	
	printf("PASSED: Pop Work!\n");
		
}

void TestPopWithEmptyStack(){
	
	int item;
	Stack* testStack;
	printf("Test pop with empty stack:");
	testStack = StackCreate(5, 5);
	
	if(StackPop(testStack, &item) != ERR_UNDERFLOW){

		printf("FAILURE\n");
	}	
		
	
	printf("PASSED: Pop Work!\n");
		
}

void PopWithNullPoiner(){
	
	int* item = NULL;
	Stack* testStack;
	testStack = StackCreate(5, 5);
	printf("Test Top With Null Pointer:");
	
	
	if(StackPop(testStack, item) != ERR_NOT_INITIALIZED){
			printf("FAILURE\n");
			return;
		}	
	
	printf("PASSED: Pop rejects NULL Pointer!\n");
	return;	
}



int main(){

	char* string = {"sdfsdf(ffghj)fghfgh{fghjfh}"}
	CheckBraces(string);

	TestStackCreat();
	TestStackCreatWith0Size();
	TestStackBlockIs0();
	TestStackPush();
	PushWith0Block();
	PushWithResize();
	PushWithNullStack();
	TopAfterPush();
	TopWithNullPoiner();
	TestTStackIsEmptyWhenStackEmpty();
	TestTStackIsEmptyAfterPush();
	PopWithNullStack();
	TestPopAfterPush();
	TestPopAfterResize();
	TestPopWithEmptyStack();
	PopWithNullPoiner();
	
	return
}
