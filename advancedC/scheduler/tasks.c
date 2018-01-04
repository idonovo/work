#include <stdlib.h>
#include "tasks.h"

#define MAGIC 0xDADADADA
#define IS_A_TASK(h) ((h) && ((h)->m_magic == MAGIC))

struct Task
{
	unsigned int	m_magic;
	TaskFunction	m_task;
	Time*			m_nextTime;
	void*			m_context;
	int				m_interval;
};

/*************************************************/
Task* TaskCreate(TaskFunction _taskFunc, void* _context, int _period_ms, const clockid_t m_clockID)
{
	Task* newTask;
	
	if(NULL == _taskFunc || 0 > _period_ms || m_clockID < 0 || !(newTask = malloc(sizeof(Task))))
	{
		return NULL;
	}
	
	newTask->m_nextTime = CreateTime(m_clockID);
	if(NULL == newTask->m_nextTime)
	{
		return NULL;
	}
	
	TimeGetNextInterval(newTask->m_nextTime, _period_ms);
	
	newTask->m_magic = MAGIC; 
	newTask->m_task = _taskFunc; 
	newTask->m_context = _context;
	newTask->m_interval = _period_ms; 
	
	return newTask;
}

/****************************************/	
void TaskDestroy(Task* _task)
{
	if(!IS_A_TASK(_task))
	{
		return;
	}
	TimeDestroy(_task->m_nextTime);
	_task->m_magic  = 1;
	free(_task);
	return;
}

/****************************************/	
void TaskCalculateNext(Task* _task)
{
	if(IS_A_TASK(_task))
	{
		TimeGetNextInterval(_task->m_nextTime, _task->m_interval);
	}
	return;
}

/****************************************/
int	TaskExecute(Task* _task)
{
	if(!IS_A_TASK(_task))
	{
		return 0;
	}
	
	TimeSleepUntil(_task->m_nextTime);
	
	return _task->m_task(_task->m_context);
}

/****************************************/
int	TaskCompare(Task* _first, Task* _second)
{

	if(!(IS_A_TASK(_first)) || (!IS_A_TASK(_second)))
	{
		return -1;
	}
	
	return TimeCompare(_first->m_nextTime, _second->m_nextTime);

}
