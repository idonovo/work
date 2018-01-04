#ifndef __MYPERIODIC_
#define __MYPERIODIC__

#include <time.h>
#include "Heap.h"

typedef int (*TaskFunction) (void* _context); 

typedef Heap PriorityQueue;

typedef struct PeriodicExecutor PeriodicExecutor;

/**  
 * @brief a function to create a PeriodicExecutor object which can execute tasks functios at minimum interval between executions. The base time for calculation is based on clockid_t value recieved from user.
 * @param[in] _name: ???.
 * @param[in] _clk_id: clockid_t value for time calculations.
 * @return PeriodicExecutor* on success/ NULL if allocation failed or if  _clk_id is < 0. 
 *
 * @Warning the task functions must match the tamplate: int (*TaskFunction) (void* _context).
 */
PeriodicExecutor* PeriodicExecuterCreate(const char* _name, clockid_t _clk_id);

/**  
 * @brief a function to destroy a PeriodicExecutor object.
 * @param[in] _executor: PeriodicExecutor*to destroy.
 */
void PeriodicExecutorDestroy(PeriodicExecutor* _executor);

/**  
 * @brief a function to add tasks function to PeriodicExecutor object.
 * @param[in] _executor: PeriodicExecutor* object to add tasks.
 * @param[in] _task: task function to execute.
 * @param[in] _context(optional): void* with addtional context for execution of the task function.
 * @param[in] _period_ms: minimum interval, in miliceconds, between executions of the function. 
 * @return 1 on success/ 0 on failure due to the folloing reasons: NULL _executor* / NULL _task / _period_ms < 0/ allocation failed. 
 */
int PeriodicExecutorAdd(PeriodicExecutor* _executor, TaskFunction _task, void* _context, int _period_ms);

/**  
 * @brief a function to run tasks on PeriodicExecutor object until completion or until pause request from the user.
 * @param[in] _executor: PeriodicExecutor* object to run.
 * @return size_t number of executions of tasks. Returned 0 could indicate NULL _executor or empty _executor.  
 */
size_t PeriodicExecutorRun(PeriodicExecutor* _executor);

/**  
 * @brief a function to pasue a runnig PeriodicExecutor object.
 * @param[in] _executor: PeriodicExecutor* object to pause.
 * @return size_t number of remaininig tasks of the _executor. Returned 0 could indicate NULL _executor or no remaining tasks.  
 */
size_t PeriodicExecutorPause(PeriodicExecutor* _executor);

#endif /*__MYPERIODIC__*/







