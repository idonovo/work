#ifndef __MYTASK__
#define __MYTASK__

#include <time.h>
#include "mytime.h"


typedef struct Task Task;

typedef int (*TaskFunction) (void* _context); 

/**  
 * @brief a function to create executable time object . 
 * @param[in] _task: function to execute. 
 * @param[in] _context: optional context for thefunction.
 * @param[in] _period_ms: minimum interval between executions of the function. 
 * @param[in] m_clockID: _clockid_t value for base calculation of time.
 * @return Task* in success r NULL if function parameter in NULL or if m_clockID/_period_ms are invalid (less than 0). 
 * @Warning the task function must match the tamplate: int (*TaskFunction) (void* _context).
 */
Task* TaskCreate(TaskFunction _task, void* _context, int _period_ms, const clockid_t m_clockID);

/**  
 * @brief a function to destroy task object.
 * @param[in] task* object.
 */	
void TaskDestroy(Task*);

/**  
 * @brief a function to calculate next interval to execute a task. 
 * @param[in] _task: task object to execute. 
 */
void TaskCalculateNext(Task* _task);

/**  
 * @brief a function to execute a task function held by Task object. 
 * @param[in] _task: Task object to execute function contained by it. 
 * @return the task function return or 0 if _task is NULL; 
 */
int	TaskExecute(Task* _task);

/**  
 * @brief a function to compare between two Task objects next interval of executing the Tasks's functions. 
 * @param[in] _first: Task object. 
 * @param[in] _second: Task object.
 * @return 1 if the first Task is earliest/ 0 if second task is earliest.
 */
int	TaskCompare(Task* _first, Task* _second);


#endif /*__MYTASK_*/
