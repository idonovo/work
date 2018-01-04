
#include <stdio.h>

#include "genbubble.h"

typedef struct Person Person;

struct Person
{
	int 	m_id;
	char 	m_name[100];
	int 	m_age;
};

int BigToSmallPerName(const void* _x, const void* _y){
	
	Person* x = (Person*)_x;
	Person* y = (Person*)_y;
	
	if(strcmp(x->m_name, y->m_name) >= 0)
	{
		return 0; 
	}
	return 1;	
}

int SmallToBigPerName(const void* _x, const void* _y){

	Person* x = (Person*)_x;
	Person* y = (Person*)_y;
	
	if(strcmp(x->m_name, y->m_name) <= 0)
	{
		return 0; 
	}
	return 1;	
}

int BigToSmallPer(const void* _x, const void* _y){
	
	Person* x = (Person*)_x;
	Person* y = (Person*)_y;
	
	if(x->m_id > y->m_id)
	{
		return 0; 
	}
	return 1;	
}

int SmallToBigPer(const void* _x, const void* _y){

	Person* x = (Person*)_x;
	Person* y = (Person*)_y;
	
	if(x->m_id < y->m_id)
	{
		return 0; 
	}
	return 1;	
}

int BigToSmallInt(const void* _x, const void* _y){

	if(*(int*)_x > *(int*)_y)
	{
		return 0; 
	}
	return 1;	
}

int SmallToBigInt(const void* _x, const void* _y){

	if(*(int*)_x > *(int*)_y)
	{
		return 1; 
	}
	return 0;	
}

int BigToSmallChar(const void* _x, const void* _y){

	if(*(char*)_x > *(char*)_y)
	{
		return 0; 
	}
	return 1;	
}

int SmallToBigChar(const void* _x, const void* _y){

	if(*(char*)_x > *(char*)_y)
	{
		return 1; 
	}
	return 0;	
}

/***********************************************************************/

void NullHowToSort(){

	int arr[5] = {7, 3, 2, 6, 4};
	void* ptr = arr;
	if(GenericBubble(ptr, 5, sizeof(int), NULL) == ERR_NOT_INITIALIZED)
	{
		printf("PASS   ");
		printf("NullHowToSort\n");
		return;
	}
	printf("Fail   ");
	printf("NullHowToSort\n");
	return;
}

void NullData(){

	if(GenericBubble(NULL, 5, sizeof(int), SmallToBigInt) == ERR_NOT_INITIALIZED)
	{
		printf("PASS   ");
		printf("NullData\n");
		return;
	}
	printf("Fail   ");
	printf("NullData\n");
	return;
}

void ZeroSize(){

	int arr[5] = {7, 3, 2, 6, 4};
	void* ptr = arr;
	if(GenericBubble(ptr, 5, 0, SmallToBigInt) == ERR_INVALID_SIZE)
	{
		printf("PASS   ");
		printf("ZeroSize\n");
		return;
	}
	printf("Fail   ");
	printf("ZeroSize\n");
	return;
}

void NoNumToSort(){

	int arr[1] = {7};
	void* ptr = arr;
	if(GenericBubble(ptr, 1, sizeof(int), SmallToBigInt) == ERR_OK)
	{
		printf("PASS   ");
		printf("NoNumToSort\n");
		return;
	}
	printf("Fail   ");
	printf("NoNumToSort\n");
	return;
}


void SortPosIntInc(){

	int arr[5] = {7, 3, 2, 6, 4};
	void* ptr = arr;
	GenericBubble(ptr, 5, sizeof(int),SmallToBigInt);
	if(arr[4] == 7)
	{
		printf("PASS   ");
		printf("SortPosIntInc\n");
		return;
	}
	printf("Fail   ");
	printf("SortPosIntInc\n");
	return;
}

void SortNegIntInc(){

	int arr[5] = {-7, -3, -2, -6, -4};
	void* ptr = arr;
	GenericBubble(ptr, 5, sizeof(int),SmallToBigInt);
	if(arr[4] == -2)
	{
		printf("PASS   ");
		printf("SortNegIntInc\n");
		return;
	}
	printf("Fail   ");
	printf("SortNegIntInc\n");
	return;
}

void SortSameIntInc(){

	int arr[5] = {-7, -4, -2, -6, -4};
	void* ptr = arr;
	GenericBubble(ptr, 5, sizeof(int),SmallToBigInt);
	if(arr[4] == -2)
	{
		printf("PASS   ");
		printf("SortSameIntInc\n");
		return;
	}
	printf("Fail   ");
	printf("SortSameIntInc\n");
	return;
}

void SortPosIntDec(){

	int arr[5] = {7, 3, 2, 6, 4};
	void* ptr = arr;
	GenericBubble(ptr, 5, sizeof(int),BigToSmallInt);
	if(arr[4] == 2)
	{
		printf("PASS   ");
		printf("SortPosIntNeg\n");
		return;
	}
	printf("Fail   ");
	printf("SortPosIntNeg\n");
	return;
}

void SortNegIntDec(){

	int arr[5] = {-7, -3, -2, -6, -4};
	void* ptr = arr;
	GenericBubble(ptr, 5, sizeof(int),BigToSmallInt);
	if(arr[4] == -7)
	{
		printf("PASS   ");
		printf("SortNegIntNeg\n");
		return;
	}
	printf("Fail   ");
	printf("SortNegIntNeg\n");
	return;
}

void SortSameIntDec(){

	int arr[5] = {-7, -4, -2, -6, -4};
	void* ptr = arr;
	GenericBubble(ptr, 5, sizeof(int),BigToSmallInt);
	if(arr[4] == -7)
	{
		printf("PASS   ");
		printf("SortSameIntDec\n");
		return;
	}
	printf("Fail   ");
	printf("SortSameIntDec\n");
	return;
}

void SortCharsInc(){

	char arr[5] = {'r', 'q', 'c', 'o', 'd'};
	void* ptr = arr;
	GenericBubble(ptr, 5, sizeof(char), SmallToBigChar);
	if(arr[4] == 'r')
	{
		printf("PASS   ");
		printf("SortCharInc\n");
		return;
	}
	printf("Fail   ");
	printf("SortCharInc\n");
	return;
}

void SortCharsDec(){

	char arr[5] = {'r', 'q', 'c', 'o', 'd'};
	void* ptr = arr;
	GenericBubble(ptr, 5, sizeof(char),BigToSmallChar);
	if(arr[4] == 'c')
	{
		printf("PASS   ");
		printf("SortCharDec\n");
		return;
	}
	printf("Fail   ");
	printf("SortCharDec\n");
	return;
}

void SortPersonIdInc(){

	Person arr[5]; 
	void* ptr = arr;
	
	arr[0].m_id = 86423423;
	arr[1].m_id = 12365423;
	arr[2].m_id = 76314633;
	arr[3].m_id = 90677524;
	arr[4].m_id = 12375648;
	
	GenericBubble(ptr, 5, sizeof(Person), SmallToBigPer);
	if(arr[4].m_id == 90677524)
	{
		printf("PASS   ");
		printf("SortPersonIdInc\n");
		return;
	}
	printf("Fail   ");
	printf("SortPersonIdInc\n");
	return;
}

void SortPersonIdDec(){

	Person arr[5]; 
	void* ptr = arr;
	
	arr[0].m_id = 86423423;
	arr[1].m_id = 12365423;
	arr[2].m_id = 76314633;
	arr[3].m_id = 90677524;
	arr[4].m_id = 12375648;
	
	GenericBubble(ptr, 5, sizeof(Person),BigToSmallPer);
	if(arr[4].m_id == 12365423)
	{
		printf("PASS   ");
		printf("SortPersonIdDec\n");
		return;
	}
	printf("Fail   ");
	printf("SortPersonIdDec\n");
	return;
}

void SortPersonNameInc(){

	Person arr[3]; 
	void* ptr = arr;
	
	arr[0].m_name[0] = 'i';
	arr[1].m_name[0] = 's';
	arr[2].m_name[0] = 'r';
	
	GenericBubble(ptr, 3, sizeof(Person), SmallToBigPer);
	if(arr[2].m_name[2] == 's')
	{
		printf("PASS   ");
		printf("SortPersonNameInc\n");
		return;
	}
	printf("Fail   ");
	printf("SortPersonNameInc\n");
	return;
}

void SortPersonNameDec(){

Person arr[3]; 
	void* ptr = arr;
	
	arr[0].m_name[0] = 'i';
	arr[1].m_name[0] = 's';
	arr[2].m_name[0] = 'r';
	
	GenericBubble(ptr, 3, sizeof(Person), BigToSmallPer);
	if(arr[2].m_name[2] == 'i')
	{
		printf("PASS   ");
		printf("SortPersonNameInc\n");
		return;
	}
	printf("Fail   ");
	printf("SortPersonNameInc\n");
	return;
}


int main(){
		
	NullHowToSort();
	NoNumToSort();
	NullData();
	ZeroSize();
	
	SortPosIntInc();
	SortNegIntInc();	
	SortSameIntInc();
	
	SortPosIntDec();
	SortNegIntDec();
	SortSameIntDec();
	
	SortCharsInc();
	SortCharsDec();
	
	SortPersonIdInc();
	SortPersonIdDec();
	return 0;
}
