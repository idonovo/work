#include <stdio.h>
#include <stdlib.h>

#include "vector.h"


struct Vector

{

    int*    m_items;

    size_t  m_originalSize;   /* original allocated space for items) */

    size_t  m_size;                 /* actual allocated space for items) */

    size_t  m_nItems;           /* actual number of items */

    size_t  m_blockSize;     /* the chunk size to be allocated when no space*/

};




int TestDoesCreat(){
	
	Vector* testVector;
	printf("TestDoesCreat:");
	
	testVector = VectorCreate(5, 5);
	
	if(testVector == NULL || testVector-> m_items == NULL){
	
		printf("FAILURE\n");
		
		return -1;
	}	
		
	
	printf("PASSED: Vector Created\n");
	
	return 0;	
}

int TestCreatWith0Size(){

	Vector* testVector;
	printf("TestCreatWith0Size:");
	
	testVector = VectorCreate(0, 5);
	
	if(testVector == NULL || testVector-> m_items == NULL){
	
		printf("FAILURE\n");
		
		return -1;
	}	
		
	
	printf("PASSED: Vector With Size 0 Created\n");
	
	return 0;	
}

int TestBlockIs0(){
	
	Vector* testVector;
	
	printf("TestBlockIs0:");
	
	testVector = VectorCreate(5, 0);
	
	if(testVector == NULL || testVector-> m_items == NULL){
	
		printf("FAILURE\n");
		
		return -1;
	}	
		
	
	printf("PASSED: Vector With Block 0 Created\n");
	return 0;	
}


int TestIfAdd(){

	int item = 5;
	Vector* testVector;
	printf("TestifAdd");
	
	
	testVector = VectorCreate(5, 5);
	
	
	if(VectorAdd(testVector, item != ERR_OK)){
		printf("FAILURE\n");
		
		return -1;
	}	
		
	
	printf("PASSED: simple add sucsses\n");
	return 0;	
}

int TestAddWitblock0(){

	
	Vector* testVector;
	int item = 5;
	
	printf("TestAddWitblock0:");
	testVector = VectorCreate(1, 0);

	VectorAdd(testVector, item);
	
	if(VectorAdd(testVector, item) != ERR_OVERFLOW){
		printf("FAILURE\n");
		
		return -1;
	}	
		
	
	printf("PASSED: add with block0\n");
	return 0;	
}


int TestAddwithResize(){

	
	Vector* testVector;
	int i;
	
	printf("TestAddwithResize:");
	
	testVector = VectorCreate(4, 4);
	

	for(i=0; i<5; i++){
	
		if(VectorAdd(testVector,i) != ERR_OK){
		
			printf("FAILURE\n");
			return -1;
		
			}
		}
	printf("PASSED: add with resize\n");
	
	return 0;	
			
}


int TsstAddAfterhResize(){

	Vector* testVector;
	int i;
	printf("TestAddAfterResize:");
	
	testVector = VectorCreate(1, 4);
	

	for(i=0; i<5; i++){
	
		if(VectorAdd(testVector,i) != ERR_OK){
		
			printf("FAILURE\n");
			return -1;
		
			}
		}
	printf("PASSED: add after with resize\n");
	
	return 0;	
			
}

int TestAddNULL(){
	
	Vector* testVector = NULL;
	int item = 5;
	printf("Test Add to NULL vector:");
	
	if(VectorAdd(testVector,item) !=  ERR_GENERAL){
		
			printf("FAILURE\n");
			return -1;
		
	}
		
	printf("PASSED: NULL test\n");
	return 0;
}

int TestAddNULLARRAY(){
	
	int item = 8;
	Vector* testVector;
	printf("Test Add to NULL array:");
	testVector = VectorCreate(5, 5);
	testVector-> m_items = NULL;
	
	
	if(VectorAdd(testVector,item) !=  ERR_GENERAL){
		
			printf("FAILURE\n");
			return -1;
		
	}
		
	printf("PASSED: NULL array test\n");
	return 0;
}

int ItemNumTestAfterCreate(){

	int i=6;
	Vector* testVector;
	printf("ItemNumTestAfterCreate:");
	testVector = VectorCreate(5, 5);
	
	if(VectorItemsNum(testVector, &i) != ERR_OK){
		printf("FAILURE\n");
		return -1;
		
	}
		
	printf("PASSED: recieved ItemNum After Create\n");
	
	return 0;	
}


int ItemNumTestAfterAdd(){

	int i;
	int item = 5;
	Vector* testVector;
	printf("ItemNum Test After add:");
	testVector = VectorCreate(5, 5);
		
	for(i=0; i<4; i++){
	
		VectorAdd(testVector, i);
	}
	
	if(VectorItemsNum(testVector, &item) != ERR_OK){
		printf("FAILURE\n");
		return -1;
		
	}
		
	printf("PASSED: recieved ItemNum After Add\n");
	
	return 0;	
}

int TestItemNumWithNULLVector(){
	
	Vector* testVector = NULL;
	int* ptr;
	printf("Test ItemNum With NULL Vector:");
	
	if(VectorItemsNum(testVector, ptr)  !=  ERR_NOT_INITIALIZED){
		
			printf("FAILURE\n");
			return -1;
		
	}
		
	printf("PASSED: NULL test\n");
	return 0;
}

int TestItemNumWithNULLArray(){
	
	
	Vector* testVector;
	int* ptr;
	printf("Test Item Num With NULL Array:");
	testVector = VectorCreate(5, 5);
	testVector-> m_items = NULL;
	
	
	if(VectorItemsNum(testVector, ptr)  !=  ERR_NOT_INITIALIZED){
		
			printf("FAILURE\n");
			return -1;
		
	}
		
	printf("PASSED: NULL array test\n");
	return 0;
}

int TestItemNumWithNULLPointer(){
	
	Vector* testVector;
	int* ptr = NULL;
	printf("Test ItemNum With NULL pointer:");
	
	testVector = VectorCreate(5, 5);
	
	if(VectorItemsNum(testVector, ptr)  !=  ERR_NOT_INITIALIZED){
		
			printf("FAILURE\n");
			return -1;
		
	}
		
	printf("PASSED: NULL array pointer\n");
	return 0;
}
/***************************************************************/

int TestIfSetWork(){

	int i;
	Vector* testVector;
	testVector = VectorCreate(5, 5);
	
	printf("Test If Set Work:");
	
	for(i=0; i<10; i++){
	
		VectorAdd(testVector, i);
	}

	if(VectorSet(testVector, 2, 4)  == ERR_OK){
	
		printf("FAILURE\n");
		return -1;
		
	}
		
	printf("PASSED: Set works!\n");
	return 0;
	
}


int TestInvalidIndex(){
	
	int index = -100;
	Vector* testVector;
	printf("Test set with Invalid Index:");
	
	testVector = VectorCreate(5, 5);
	
	
	if(VectorSet(testVector, -10, index)  ==  ERR_UNDERFLOW){
		
			printf("FAILURE\n");
			return -1;
		
	}
		
	printf("PASSED: set rejects invalid index\n");
	return 0;
}

int TestSetNULLVector(){
	
	
	Vector* testVector = NULL;
	printf("Test Set NULL Vector:");
	
	if(VectorSet(testVector, 1, 2)  !=  ERR_NOT_INITIALIZED){
		
			printf("FAILURE\n");
			return -1;
		
	}
		
	printf("PASSED: NULL test\n");
	return 0;
	
}

int TestSetWithNULLArray(){
	
	Vector* testVector;
	testVector = VectorCreate(5, 5);
	testVector-> m_items = NULL;
	printf("Test Set With NULL Array:");
	testVector = VectorCreate(5, 5);
	
	
	
	if(VectorSet(testVector, 1, 2)  ==  ERR_NOT_INITIALIZED){
		
			printf("FAILURE\n");
			return -1;
		
	}
		
	printf("PASSED: NULL array test\n");
	return 0;
	
}


int TestIfGetWork(){

	int i;
	int item;
	Vector* testVector;
	testVector = VectorCreate(5, 5);
	printf("Test If Get Work:");
	
	
	for(i=0; i<10; i++){
	
		VectorAdd(testVector, i);
	}

	if(VectorGet(testVector, 2, &item)  != ERR_OK){
	
		printf("FAILURE\n");
		return -1;
		
	}
		
	printf("PASSED: Set works!\n");
	return 0;
	
}


int TestSetInvalidIndex(){
	
	int index = -100;
	Vector* testVector;
	testVector = VectorCreate(5, 5);
	printf("Test Get with Invalid Index:");
	
	if(VectorGet(testVector, -10, &index)  ==  ERR_UNDERFLOW){
		
			printf("FAILURE\n");
			return -1;
		
	}
		
	printf("PASSED: set rejects invalid index\n");
	return 0;
}

int TestGetNULLVector(){
	
	Vector* testVector = NULL;
	int item;
	printf("Test Get NULL Vector:");
		
	if(VectorGet(testVector, 1, &item)  !=  ERR_NOT_INITIALIZED){
		
			printf("FAILURE\n");
			return -1;
		
	}
		
	printf("PASSED: NULL test\n");
	return 0;
	
}

int TestGetWithNULLArray(){
	
	Vector* testVector;
	int item;
	
	printf("Test Get With NULL Array:");
	testVector = VectorCreate(5, 5);
	testVector-> m_items = NULL;
	
	
	if(VectorGet(testVector, 1, &item)  ==  ERR_NOT_INITIALIZED){
		
			printf("FAILURE\n");
			return -1;
		
	}
		
	printf("PASSED: NULL array test\n");
	return 0;
}

int TestIfDeleteWithResizeWork(){

	int i;
	int item;
	Vector* testVector;
	
	printf("Test Delete Get Work:");
	testVector = VectorCreate(5, 5);
	
	
	
	
	for(i=0; i<5; i++){
	
		VectorAdd(testVector, i);
	}

	if(VectorDelete(testVector, &item) != ERR_OK){
	
		printf("FAILURE\n");
		return -1;
		
	}
		
	printf("PASSED: Delete works!\n");
	return 0;
	
}

int TestDeleteUnderflow(){
	
	Vector* testVector;
	int item;
	testVector = VectorCreate(5, 5);
	printf("Test Delete Underflow:");
	
	
	if(VectorDelete(testVector, &item) != ERR_UNDERFLOW){
	
		printf("FAILURE\n");
		return -1;
		
	}
		
	printf("PASSED: Delete works!\n");
	return 0;
}

int TestDeleteNULLVector(){
	
	int item;
	Vector* testVector = NULL;
	printf("Test Delete NULL Vector:");
		
	if(VectorDelete(testVector, &item) !=  ERR_NOT_INITIALIZED){
		
			printf("FAILURE\n");
			return -1;
		
	}
		
	printf("PASSED: NULL test\n");
	return 0;
	
}

int TestDeleteWithNULLArray(){
	
	
	Vector* testVector;
	int item;
	printf("Test Delete With NULL Array:");
	testVector = VectorCreate(5, 5);
	testVector-> m_items = NULL;
	
	
	if(VectorDelete(testVector, &item) ==  ERR_NOT_INITIALIZED){
		
			printf("FAILURE\n");
			return -1;
		
	}
		
	printf("PASSED: NULL test\n");
	return 0;
	
}

int TestDeleteWithNULLPtr(){
	
	Vector* testVector;
	int* item = NULL;
	printf("Test Delete With NULL Ptr:");
	
	testVector = VectorCreate(5, 5);
	
	if(VectorDelete(testVector, item) !=  ERR_NOT_INITIALIZED){
		
			printf("FAILURE\n");
			return -1;
		
	}
		
	printf("PASSED: NULL test\n");
	return 0;
}

int TestIfDeleteWithEmptyArray(){
	
	int item;
	Vector* testVector;
	testVector = VectorCreate(5, 5);
	
	printf("Test Delete With Empty Array:");

	if(VectorDelete(testVector, &item) == ERR_UNDERFLOW){
	
		printf("FAILURE\n");
		return -1;
		
	}
		
	printf("PASSED: Delete works!\n");
	return 0;

}

int main(){

TestDoesCreat();
TestCreatWith0Size();
TestBlockIs0();
TestIfAdd();
TestAddWitblock0();
TestAddwithResize();
TsstAddAfterhResize();
TestAddNULL();
TestAddNULLARRAY();
ItemNumTestAfterCreate();
ItemNumTestAfterAdd();
TestItemNumWithNULLVector();
TestItemNumWithNULLArray();
TestItemNumWithNULLPointer();
TestIfSetWork();
TestInvalidIndex();
TestSetNULLVector();
TestSetWithNULLArray();
TestIfGetWork();
TestGetNULLVector();
TestGetWithNULLArray();
TestIfDeleteWithResizeWork();
TestDeleteUnderflow();
TestDeleteNULLVector();
TestDeleteWithNULLArray();
TestDeleteWithNULLPtr();
TestIfDeleteWithEmptyArray();

return 0;
}

