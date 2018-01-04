#include <stdlib.h>
#include "tasks.h"
#include "../../inc/preiodic.h"

#define SIZE 100
#define IS_AN_EXECUTER(h) ((h) && ((h)->m_magic == MAGIC))
#define MAGIC 0xDBBDADA

struct PeriodicExecutor
{
	unsigned int	m_magic;
	PriorityQueue*	m_priorityQ;
	size_t			m_runCycles;
	int				m_pauseRequest;
	const char*		m_name;
	clockid_t		m_clockID;
};
/*****************************************************************/

/* a function to dreate priority queue to run (base on a heap). Return a pointer to the queue on success or NULL in failure*/
static PriorityQueue* CreatePriorityQueue(void);

/* a function to destroy priority queue (base on a heap)*/
void DestroyQueue(PriorityQueue* _queue);

/* a function to insert tasks into priority queue (based od a heap). Return 0 on success or 1 if it failed  */
int InsertToQueue(PriorityQueue* _queue, Task* _task);

/* a function to insert check num. of remaining tasks in a queue (based od a heap). Return number of the remaining tasks  */
size_t RemainingTasksInQueue(PriorityQueue* _queue);

/* a function to recieve next task from a queue (based od a heap). Return pointer to a task on success or NULL on failure */
Task* GetNextTask(PriorityQueue* _queue);


/********************************************/
static PriorityQueue* CreatePriorityQueue(void)
{
	PriorityQueue* newQueue;
	Vector* vector;
	
	vector = VectorCreate(SIZE, SIZE);
	if(!vector)
	{
		return NULL;
	}
	
	newQueue = HeapBuild(vector, (LessThanComparator)TaskCompare);
	
	return newQueue;  	
}

PeriodicExecutor* PeriodicExecuterCreate(const char* _name, clockid_t _clk_id)
{
	
	PeriodicExecutor* newExecutor;
	
	if(0 > _clk_id)
	{
		return NULL;
	}
	
	newExecutor = malloc(sizeof(PeriodicExecutor));
	if(!newExecutor)
	{
		return NULL;
	}
	
	newExecutor->m_priorityQ = CreatePriorityQueue();
	if(!newExecutor->m_priorityQ)
	{
		return NULL;
	}
	
	newExecutor->m_magic = MAGIC;
	newExecutor->m_runCycles = 0;
	newExecutor->m_pauseRequest = 0;
	newExecutor->m_name = _name;
	newExecutor->m_clockID = _clk_id;

	return newExecutor;
}
/**********************************************************************/

void DestroyQueue(PriorityQueue* _queue)
{
	Vector* vecToDest; 
	vecToDest = HeapDestroy(&_queue);
	VectorDestroy(&vecToDest, (_elementDestroy)TaskDestroy);
	return;
}

void PeriodicExecutorDestroy(PeriodicExecutor* _executor)
{

	if(!IS_AN_EXECUTER(_executor))
	{
	    return;
	}
	
	if(_executor->m_priorityQ)
	{
		DestroyQueue(_executor->m_priorityQ);
	}
	_executor->m_magic  = 1;
	free(_executor);
	return;	
}
/*******************************************************************************************/
int InsertToQueue(PriorityQueue* _queue, Task* _task)
{
	if(HeapInsert(_queue, _task) != HEAP_SUCCESS)
	{
		return 0;
	}
	return 1;
}

int PeriodicExecutorAdd(PeriodicExecutor* _executor, TaskFunction _task, void* _context, int _period_ms)
{
	Task* newTask;
	
	if(!IS_AN_EXECUTER(_executor) || NULL == _task || NULL == _executor->m_priorityQ || _period_ms < 0)
	{
		return 0;
	}
	
	newTask = TaskCreate(_task, _context, _period_ms, _executor->m_clockID);
	if(!newTask)
	{
		return 0;
	}
	
	return InsertToQueue(_executor->m_priorityQ, newTask); 
}
/*************************************************************************************/
size_t RemainingTasksInQueue(PriorityQueue* _queue)
{
	return HeapSize(_queue);
}

Task* GetNextTask(PriorityQueue* _queue)
{
	Task* taskToRun;
	
	return (taskToRun =  HeapExtract(_queue));
}

size_t PeriodicExecutorRun(PeriodicExecutor* _executor)
{
	Task* taskToRun;
	
	if(!IS_AN_EXECUTER(_executor))
	{
	    return 0;
	}
	_executor->m_pauseRequest = 1;
	
	while(0 != RemainingTasksInQueue(_executor->m_priorityQ) && 0 != _executor->m_pauseRequest)
	{
		taskToRun = GetNextTask(_executor->m_priorityQ);
	
		if(TaskExecute(taskToRun))
		{
			TaskCalculateNext(taskToRun);
			InsertToQueue(_executor->m_priorityQ, taskToRun);
		}
		++_executor->m_runCycles;
	}
	return _executor->m_runCycles;
}

/***************************************************************************/
size_t PeriodicExecutorPause(PeriodicExecutor* _executor)
{
	if(!IS_AN_EXECUTER(_executor))
	{
	    return 0;
	}
	_executor->m_pauseRequest = 0;
	
	return RemainingTasksInQueue(_executor->m_priorityQ);
}
