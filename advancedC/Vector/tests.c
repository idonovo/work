#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "mu_test.h"
#include "../../inc/genVec.h"

void DestroyVar(void* _item){

	free(_item);
	return;
}

int PrintInt(void* _item1, void* _item2){

	printf("%d  ", *(int*)_item1); 
	return 1;
}

/*
UNIT(TestIsCreate)

    void *handle;
    Vector* testVector;
    Vector* (*cosine)(size_t _initialCapacity, size_t _blockSize);

    handle = dlopen ("/home/ido/Desktop/work/advanced C/Vector/vecll.dll", RTLD_LAZY);
    cosine = dlsym(handle, "VectorCreate");
	testVector = cosine(5, 5);
	ASSERT_THAT(testVector != NULL);
	free(testVector)
END_UNIT
*/

/******************************************/
UNIT(TestIsCreate)

	Vector* testVector;
	testVector = VectorCreate(5, 5);
	ASSERT_THAT(testVector != NULL);
	free(testVector)
END_UNIT



UNIT(TestCreatWith0Size)
	Vector* testVector;
	testVector = VectorCreate(4, 0);
	ASSERT_THAT(testVector != NULL);
	free(testVector);
END_UNIT

UNIT(TestCreatWith0SizeandBlock)
	Vector* testVector;
	testVector = VectorCreate(0, 0);
	ASSERT_THAT(testVector == NULL);
	free(testVector);
END_UNIT

UNIT(TestIfAppend)
	Vector* testVector;
	void* x; 
	int *y = malloc(sizeof(int));
	*y=8;
	x = y;
	testVector = VectorCreate(5, 5);
	ASSERT_THAT(VectorAppend(testVector, x) == ERR_OK);
	VectorDestroy(&testVector, DestroyVar);
END_UNIT

UNIT(TestAppendWitblock0)
	Vector* testVector;
	int* y[2];
	void* x;
	void* q;
	
	y[0] = malloc(sizeof(int));
	y[1] = malloc(sizeof(int));
	*y[0]=8;
	*y[1]=8;
	x = y[0]; 
	q = y[1];
	testVector = VectorCreate(1, 0);
	VectorAppend(testVector, x);
	ASSERT_THAT(VectorAppend(testVector, q) == ERR_OVERFLOW);
	VectorDestroy(&testVector, DestroyVar);
END_UNIT

UNIT(TestAppendwithResize)

	Vector* testVector;
	int* y[2];
	void* x;
	void* q;
	
	y[0] = malloc(sizeof(int));
	y[1] = malloc(sizeof(int));
	*y[0]=10;
	*y[1]=8;
	x = y[0]; 
	q = y[1];
	testVector = VectorCreate(1, 1);
	VectorAppend(testVector, x);
	ASSERT_THAT(VectorAppend(testVector, q) == ERR_OK);
	VectorDestroy(&testVector, DestroyVar);
	
END_UNIT

UNIT(TestAppendNullVector)
	
	Vector* testVector = NULL;
	void* x = NULL;
	ASSERT_THAT(VectorAppend(testVector, x) ==  ERR_NOT_INITIALIZED);
	
END_UNIT

UNIT(TestAppendNullPtr)

	Vector* testVector;
	void* x = NULL;
	testVector = VectorCreate(1, 1);
	ASSERT_THAT(VectorAppend(testVector, x) ==  ERR_NOT_INITIALIZED);
	VectorDestroy(&testVector, DestroyVar);
	
END_UNIT

UNIT(TestIsRemove)
	
	Vector* testVector;
	void* x;
	void* q;
	void* w;
	int* y[2];
	
	y[0] = malloc(sizeof(int));
	y[1] = malloc(sizeof(int));
	*y[0]=8;
	*y[1]=4;
	x = y[0]; 
	q = y[1];
	testVector = VectorCreate(1, 1);
	VectorAppend(testVector, x);
	VectorAppend(testVector, q);
	ASSERT_THAT(VectorRemove(testVector, &w) == ERR_OK);
	VectorDestroy(&testVector, DestroyVar);
	
END_UNIT

UNIT(TestIsRemoveUnderflow)

	Vector* testVector;
	void* w;

	testVector = VectorCreate(1, 1);
	ASSERT_THAT(VectorRemove(testVector, &w) == ERR_UNDERFLOW);
	VectorDestroy(&testVector, DestroyVar);
	
END_UNIT

UNIT(TestIsRemoveAfterResize)

	Vector* testVector;
	void* x;
	void* q;
	int* y[2];
	
	y[0] = malloc(sizeof(int));
	y[1] = malloc(sizeof(int));
	*y[0]=8;
	*y[1]=4;
	x = y[0]; 
	q = y[1];
	testVector = VectorCreate(1, 1);
	VectorAppend(testVector, x);
	VectorAppend(testVector, q);
	ASSERT_THAT(VectorRemove(testVector, &x) == ERR_OK);
	VectorDestroy(&testVector, DestroyVar);

END_UNIT

UNIT(TestRemoveFromNullVector)
	
	Vector* testVector = NULL;
	void** x = NULL;
	ASSERT_THAT(VectorRemove(testVector, x) ==  ERR_NOT_INITIALIZED);
	
END_UNIT
	
UNIT(TestIsVectorGet)
	
	Vector* testVector;
	void* x;
	void* q;
	void* w = NULL;
	int* y[2];
	
	y[0] = malloc(sizeof(int));
	y[1] = malloc(sizeof(int));
	*y[0]=8;
	*y[1]=4;
	x = y[0]; 
	q = y[1];
	testVector = VectorCreate(1, 1);
	VectorAppend(testVector, x);
	VectorAppend(testVector, q);
	ASSERT_THAT(VectorGet(testVector, 1, &w) == ERR_OK);
	VectorDestroy(&testVector, DestroyVar);
	
END_UNIT

UNIT(TestVectorGetNegIndex)
	
	Vector* testVector;
	void* x;
	void* q;
	void* w = NULL;
	int* y[2];
	
	y[0] = malloc(sizeof(int));
	y[1] = malloc(sizeof(int));
	*y[0]=8;
	*y[1]=4;
	x = y[0]; 
	q = y[1];
	testVector = VectorCreate(1, 1);
	VectorAppend(testVector, x);
	VectorAppend(testVector, q);
	ASSERT_THAT(VectorGet(testVector, -4, &w) == ERR_WRONG_INDEX);
	VectorDestroy(&testVector, DestroyVar);
	
END_UNIT

UNIT(TestIsVectorGetEmptyVector)
	
	Vector* testVector;
	void* w = NULL;
	
	testVector = VectorCreate(1, 1);
	ASSERT_THAT(VectorGet(testVector, 0, &w) == ERR_WRONG_INDEX);
	VectorDestroy(&testVector, DestroyVar);
	
END_UNIT


UNIT(TestIsVectorGetNullVector)

	void* w = NULL;
	ASSERT_THAT(VectorGet(NULL, 0, &w) == ERR_NOT_INITIALIZED);
	
END_UNIT


UNIT(TestVectorGetOverflowIndex)

	Vector* testVector;
	void* x;
	void* q;
	void* w = NULL;
	int* y[2];
	
	y[0] = malloc(sizeof(int));
	y[1] = malloc(sizeof(int));
	*y[0]=8;
	*y[1]=4;
	x = y[0]; 
	q = y[1];
	testVector = VectorCreate(1, 1);
	VectorAppend(testVector, x);
	VectorAppend(testVector, q);
	ASSERT_THAT(VectorGet(testVector, 4, &w) == ERR_WRONG_INDEX);
	VectorDestroy(&testVector, DestroyVar);

END_UNIT

UNIT(TestIsVectorSet)

	Vector* testVector;
	void* x;
	void* q;
	void* w;
	int* y[3];
	
	y[0] = malloc(sizeof(int));
	y[1] = malloc(sizeof(int));
	y[2] = malloc(sizeof(int));
	*y[0]=8;
	*y[1]=4;
	*y[2]=2;
	x = y[0]; 
	q = y[1];
	w = y[2];
	testVector = VectorCreate(1, 1);
	VectorAppend(testVector, x);
	VectorAppend(testVector, q);
	ASSERT_THAT(VectorSet(testVector, 1, w) == ERR_OK);
	VectorDestroy(&testVector, DestroyVar);

END_UNIT

UNIT(TestIsVectorsetEmptyVector)

	Vector* testVector;
	void* w = NULL;
	
	testVector = VectorCreate(1, 1);
	ASSERT_THAT(VectorGet(testVector, 1, w) == ERR_WRONG_INDEX);
	VectorDestroy(&testVector, DestroyVar);

END_UNIT

UNIT(TestIsVectorSetNullVector)

	void* w = NULL;
	
	ASSERT_THAT(VectorGet(NULL, 1, w) == ERR_NOT_INITIALIZED);

END_UNIT

UNIT(TestVectorSetOverflowIndex)

	Vector* testVector;
	void* x;
	void* q;
	void* w = NULL;
	int* y[2];

	y[0] = malloc(sizeof(int));
	y[1] = malloc(sizeof(int));
	*y[0]=8;
	*y[1]=4;
	x = y[0]; 
	q = y[1];
	testVector = VectorCreate(1, 1);
	VectorAppend(testVector, x);
	VectorAppend(testVector, q);
	ASSERT_THAT(VectorSet(testVector, 4, w) == ERR_WRONG_INDEX);
	VectorDestroy(&testVector, DestroyVar);;

END_UNIT

UNIT(TestVectorSetNegIndex)

	Vector* testVector;
	void* x;
	void* q;
	void* w;
	int* y[2];
	
	y[0] = malloc(sizeof(int));
	y[1] = malloc(sizeof(int));
	*y[0]=8;
	*y[1]=4;
	x = y[0]; 
	q = y[1];
	w = y[1];
	testVector = VectorCreate(1, 1);
	VectorAppend(testVector, x);
	VectorAppend(testVector, q);
	ASSERT_THAT(VectorSet(testVector, -4, w) == ERR_WRONG_INDEX);
	VectorDestroy(&testVector, DestroyVar);

END_UNIT

UNIT(TestIsGetSize)

	Vector* testVector;
	void* x;
	void* q;
	void* w;
	int* y[3];
	
	y[0] = malloc(sizeof(int));
	y[1] = malloc(sizeof(int));
	y[2] = malloc(sizeof(int));
	*y[0]=8;
	*y[1]=4;
	*y[1]=2;
	x = y[0]; 
	q = y[1];
	w = y[2];
	testVector = VectorCreate(1, 1);
	VectorAppend(testVector, x);
	VectorAppend(testVector, q);
	VectorAppend(testVector, w);
	ASSERT_THAT(VectorSize(testVector) == 3);
	VectorDestroy(&testVector, DestroyVar);

END_UNIT

UNIT(TestGetSizeEmptyVector)

	Vector* testVector;
	
	testVector = VectorCreate(1, 1);
	ASSERT_THAT(VectorSize(testVector) == 0);
	VectorDestroy(&testVector, DestroyVar);
	
END_UNIT

UNIT(TestIsGetCapacity)

	Vector* testVector;
	void* x;
	void* q;
	void* w;
	int* y[2];
	
	y[0] = malloc(sizeof(int));
	y[1] = malloc(sizeof(int));
	*y[0]=8;
	*y[1]=4;
	x = y[0]; 
	q = y[1];
	w = y[1];
	testVector = VectorCreate(1, 5);
	VectorAppend(testVector, x);
	VectorAppend(testVector, q);
	VectorAppend(testVector, w);
	ASSERT_THAT(VectorCapacity(testVector) == 6);
	VectorDestroy(&testVector, NULL);

END_UNIT

UNIT(TestGetCapacityEmptyVector)

	Vector* testVector;
	
	testVector = VectorCreate(1, 1);
	ASSERT_THAT(VectorCapacity(testVector) == 1);
	VectorDestroy(&testVector, DestroyVar);
	
END_UNIT

UNIT(TestIfDestroy2IntItems)

	int* y[2] ;
	Vector* testVector;
	void* x;
	void* q;
	
	y[0] = malloc(sizeof(int));
	y[1] = malloc(sizeof(int));
	*y[0]=8;
	*y[1]=8;
	x = y[0]; 
	q=y[1];
	testVector = VectorCreate(5, 5);
	VectorAppend(testVector, x);
	VectorAppend(testVector, q);
	VectorDestroy(&testVector, DestroyVar);
	ASSERT_THAT(testVector != NULL)
	
END_UNIT

UNIT(TestIfDestroy2CharItems)

	char* y[2] ;
	void* x;
	void* q;
	Vector* testVector;
	
	y[0] = malloc(sizeof(char));
	y[1] = malloc(sizeof(char));	
	*y[0]='t';
	*y[1]='w';
	x = y[0]; 
	q=y[1];
	testVector = VectorCreate(5, 5);
	VectorAppend(testVector, x);
	VectorAppend(testVector, q);
	VectorDestroy(&testVector, DestroyVar);
	ASSERT_THAT(testVector != NULL);
	
END_UNIT

UNIT(TestIfPrint4IntItems)

	int* y[2] ;
	Vector* testVector;
	void* x;
	void* q;
	
	y[0] = malloc(sizeof(int));
	y[1] = malloc(sizeof(int));
	
	*y[0]=34534533;
	*y[1]=123;
	x = y[0]; 
	q=y[1];
	testVector = VectorCreate(5, 5);
	VectorAppend(testVector, x);
	VectorAppend(testVector, q);
	VectorAppend(testVector, x);
	VectorAppend(testVector, q);
	ASSERT_THAT(4 == VectorForEach(testVector, PrintInt, NULL));
	VectorDestroy(&testVector, DestroyVar);
	
END_UNIT


TEST_SUITE(framework test)
	TEST(TestIsCreate)
	TEST(TestCreatWith0Size)
	TEST(TestCreatWith0SizeandBlock)
	TEST(TestIfAppend)
	TEST(TestAppendWitblock0)
	TEST(TestAppendwithResize)
	TEST(TestAppendNullVector)
	TEST(TestAppendNullPtr)
	TEST(TestIsRemove)
	TEST(TestIsRemoveUnderflow)
	TEST(TestIsRemoveAfterResize)
	TEST(TestRemoveFromNullVector)
	TEST(TestIsVectorGet)
	TEST(TestIsVectorGetEmptyVector)
	TEST(TestVectorGetNegIndex)
	TEST(TestIsVectorGetEmptyVector)
	TEST(TestIsVectorGetNullVector)
	TEST(TestVectorGetOverflowIndex)
	TEST(TestIsVectorSet)
	TEST(TestIsVectorsetEmptyVector)
	TEST(TestIsVectorSetNullVector)
	TEST(TestVectorSetOverflowIndex)
	TEST(TestVectorSetNegIndex)
    TEST(TestIsGetSize)
	TEST(TestGetSizeEmptyVector)
	TEST(TestIsGetCapacity)
	TEST(TestGetCapacityEmptyVector)
	TEST(TestIfDestroy2IntItems)
	TEST(TestIfDestroy2CharItems)
	TEST(TestIfPrint4IntItems)

	
END_SUITE









