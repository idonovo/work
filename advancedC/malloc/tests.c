#include <stdio.h>

#include "mymalloc.h"
#include "mu_test.h"

#define SIZE 10

UNIT(IsCreateBuffer)
	Buffer* testBuffer;
	testBuffer= CreateBuffer(10, 5);
	ASSERT_THAT(testBuffer != NULL);
	DestroyBuffer(testBuffer);
END_UNIT

UNIT(IsCreatSize0)
	Buffer* testBuffer;
	testBuffer= CreateBuffer(0, 0);
	ASSERT_THAT(testBuffer == NULL);
END_UNIT

UNIT(IsMalloc)
	Buffer* testBuffer;
	testBuffer= CreateBuffer(3, 5);
	ASSERT_THAT(MyMalloc(testBuffer) != NULL);
	DestroyBuffer(testBuffer);
END_UNIT

UNIT(IsMallocTwice)
	Buffer* testBuffer;
	testBuffer= CreateBuffer(3, 5);
	ASSERT_THAT(MyMalloc(testBuffer) != NULL);
	ASSERT_THAT(MyMalloc(testBuffer) != NULL);
	DestroyBuffer(testBuffer);
END_UNIT

UNIT(IsMallocAfterFree)
	Buffer* testBuffer;
	void* ptr;
	testBuffer= CreateBuffer(3, 5);
	ptr = MyMalloc(testBuffer);
	ptr = MyMalloc(testBuffer);
	ASSERT_THAT(ptr != NULL);
	MyFree(testBuffer, ptr);
	ASSERT_THAT(MyMalloc(testBuffer) != NULL);
	DestroyBuffer(testBuffer);
END_UNIT

UNIT(IsMallocByondBuffer)
	Buffer* testBuffer;
	void* ptr;
	testBuffer= CreateBuffer(10, 1);
	ptr = MyMalloc(testBuffer);
	ptr = MyMalloc(testBuffer);
	ASSERT_THAT(ptr == NULL);
	DestroyBuffer(testBuffer);
END_UNIT

TEST_SUITE(framework test)
	TEST(IsCreateBuffer)
	TEST(IsCreatSize0)
	TEST(IsMalloc)
	TEST(IsMallocTwice)
	TEST(IsMallocAfterFree)
	TEST(IsMallocByondBuffer)
END_SUITE

