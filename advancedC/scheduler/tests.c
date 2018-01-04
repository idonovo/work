#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mu_test.h"
#include "mytime.h"
#include "tasks.h"
#include "../../inc/preiodic.h"

int global = 0;

/*********************************************/
int PrintItem(void* _item)
{
	int i;
	for(i=0; i<10; ++i)
	printf("%d\n", *(int*)_item);
	return 0;

}

int PrintInLoop(void* _item)
{
	int i;
	for(i=0; i<10; ++i)
	{
    	printf("%d\n", *(int*)_item + i);
	}
	return 0;

}

int PauseProg(void* _item)
{
	int i;
	for(i=0; i<10; ++i)
	{
    	printf("%d\n", i);
	}
	printf("reamining tasks: %d\n", PeriodicExecutorPause((PeriodicExecutor*)_item));
	return 1;
} 

int PrintIfGlobal(void* _item)
{
	int i;
    if(global == 0)
    {
	    for(i=0; i<10; ++i)
	    {
        	printf("%d\n", i);
	    }   
	    return 1;
    }
    printf("finish!!");
    return 0;
} 

int ChangeGlobal(void* _item)
{
	global = 1;
	printf("global was changed");
	return 0;
} 

/********************************************************/
UNIT(TestIsGetNextInterval)
	Time* testTime = CreateTime(CLOCK_MONOTONIC); 
	TimeGetNextInterval(testTime, 100);
	ASSERT_THAT(testTime != NULL);
    TimeDestroy(testTime)

END_UNIT

UNIT(TestIsGetNextIntervalWithCarry)
	Time* testTime = CreateTime(CLOCK_MONOTONIC); 
	TimeGetNextInterval(testTime, 1034);
	ASSERT_THAT(testTime != NULL);
    TimeDestroy(testTime)

END_UNIT


UNIT(TestIsCompare)
	Time* testTime[2];
	testTime[0] = CreateTime(CLOCK_MONOTONIC); 
	TimeGetNextInterval(testTime[0], 100);
	testTime[1] = CreateTime(CLOCK_MONOTONIC); 
	TimeGetNextInterval(testTime[1], 200);
	ASSERT_THAT(TimeCompare(testTime[0], testTime[1]) == 0);
    TimeDestroy(testTime[0]);
    TimeDestroy(testTime[1]);
END_UNIT

UNIT(TestIsSleep)
	Time* testTime = CreateTime(CLOCK_MONOTONIC); 
	TimeGetNextInterval(testTime, 100);
    TimeSleepUntil(testTime);
    TimeDestroy(testTime);
END_UNIT

UNIT(TestIsCreateTask)
	
	Task* testTask = TaskCreate(PrintItem, NULL, 1000, CLOCK_MONOTONIC);
	ASSERT_THAT(testTask != NULL);
    TaskDestroy(testTask);
END_UNIT

UNIT(TestIsCreateTaskNullFunc)
	
	Task* testTask = TaskCreate(NULL, NULL, 1000, CLOCK_MONOTONIC);
	ASSERT_THAT(testTask == NULL);
END_UNIT

UNIT(TestIsTaskExec)	
	int x = 10;
	Task* testTask = TaskCreate(PrintItem, (void*)&x, 1000, 0);
	clock_t t;
    t = clock();
	ASSERT_THAT(TaskExecute(testTask) == 0);
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("task took %f seconds to execute \n", time_taken);
	TaskDestroy(testTask);
END_UNIT

UNIT(TestIsCompareTasks)	
	Task* testTask1 = TaskCreate(PrintItem, NULL, 1050, CLOCK_MONOTONIC);
	Task* testTask2 = TaskCreate(PrintItem, NULL, 100, CLOCK_MONOTONIC);
	ASSERT_THAT(TaskCompare(testTask1, testTask2) == 0);
	TaskDestroy(testTask1);
	TaskDestroy(testTask2);
END_UNIT

UNIT(TestIsPeriodicCreate)

    PeriodicExecutor* testPeriod = PeriodicExecuterCreate(NULL, CLOCK_MONOTONIC);
	ASSERT_THAT(testPeriod != NULL);
	PeriodicExecutorDestroy(testPeriod);
END_UNIT

UNIT(TestIsPeriodicCreateNoValidClockID)

    PeriodicExecutor* testPeriod = PeriodicExecuterCreate(NULL, -1);
	ASSERT_THAT(testPeriod == NULL);

END_UNIT

UNIT(TestIsPeriodicAdd)

    PeriodicExecutor* testPeriod = PeriodicExecuterCreate(NULL, 0);
	ASSERT_THAT(PeriodicExecutorAdd(testPeriod, PrintItem, NULL, 1000) == 1);
	PeriodicExecutorDestroy(testPeriod);

END_UNIT

UNIT(TestIsPeriodicAddMultipuleTasks)
    int i;        
     PeriodicExecutor* testPeriod = PeriodicExecuterCreate(NULL, 0);
     for(i=0;i<5; i++)
     {
        PeriodicExecutorAdd(testPeriod, PrintItem, &i, 1000);
        PeriodicExecutorAdd(testPeriod, PrintInLoop, &i, 500);
     }
	ASSERT_THAT(PeriodicExecutorAdd(testPeriod, PrintItem, NULL, 1000) == 1);
	PeriodicExecutorDestroy(testPeriod);
END_UNIT

UNIT(TestIsExecutorRun)
     int i = 10;
     PeriodicExecutor* testPeriod = PeriodicExecuterCreate(NULL, 0);
     PeriodicExecutorAdd(testPeriod, PrintItem, &i, 500);
     PeriodicExecutorAdd(testPeriod, PrintInLoop, &i, 1000);
	 ASSERT_THAT(PeriodicExecutorRun(testPeriod) != 0);
	 PeriodicExecutorDestroy(testPeriod);
END_UNIT

UNIT(TestIsExecutorRunInOrder)
     int i = 10;
     PeriodicExecutor* testPeriod = PeriodicExecuterCreate(NULL, 0);
     PeriodicExecutorAdd(testPeriod, PrintItem, &i, 1000);
     PeriodicExecutorAdd(testPeriod, PrintInLoop, &i, 500);
	 ASSERT_THAT(PeriodicExecutorRun(testPeriod) != 0);
	 PeriodicExecutorDestroy(testPeriod);
END_UNIT

UNIT(TestIsPause)
     int i = 10; 
     PeriodicExecutor* testPeriod = PeriodicExecuterCreate(NULL, 0);
     PeriodicExecutorAdd(testPeriod, PauseProg, testPeriod, 500);
     PeriodicExecutorAdd(testPeriod, PrintInLoop, &i, 1000);
	 ASSERT_THAT(PeriodicExecutorRun(testPeriod) != 0);
	 PeriodicExecutorDestroy(testPeriod);
END_UNIT

UNIT(TestIsRunTwiceSameProgram)
     int i = 10; 
     PeriodicExecutor* testPeriod = PeriodicExecuterCreate(NULL, 0);
     PeriodicExecutorAdd(testPeriod, PrintIfGlobal, testPeriod, 100);
     PeriodicExecutorAdd(testPeriod, ChangeGlobal, &i, 250);
	 ASSERT_THAT(PeriodicExecutorRun(testPeriod) != 0);
	 PeriodicExecutorDestroy(testPeriod);
END_UNIT

UNIT(TestIsRunAfterPause)
     int i = 10; 
     PeriodicExecutor* testPeriod = PeriodicExecuterCreate(NULL, 0);
     PeriodicExecutorAdd(testPeriod, PauseProg, testPeriod, 500);
     PeriodicExecutorAdd(testPeriod, PrintInLoop, &i, 1000);
	 PeriodicExecutorRun(testPeriod);
	 ASSERT_THAT(PeriodicExecutorRun(testPeriod) != 0);
	 PeriodicExecutorDestroy(testPeriod);

END_UNIT

TEST_SUITE(framework test)
	
	TEST(TestIsGetNextIntervalWithCarry)
	TEST(TestIsGetNextInterval)
	TEST(TestIsCompare)
	TEST(TestIsSleep)
	
	TEST(TestIsCreateTask)
	TEST(TestIsCreateTaskNullFunc)
	TEST(TestIsTaskExec)
	TEST(TestIsCompareTasks)
	
	TEST(TestIsPeriodicCreate)
	TEST(TestIsPeriodicCreateNoValidClockID)
	TEST(TestIsPeriodicAdd)
	TEST(TestIsPeriodicAddMultipuleTasks)
	
	TEST(TestIsExecutorRun)
	TEST(TestIsExecutorRunInOrder)
	TEST(TestIsPause)
	TEST(TestIsRunTwiceSameProgram)
	TEST(TestIsRunAfterPause)
	
END_SUITE

