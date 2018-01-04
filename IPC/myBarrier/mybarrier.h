#include <stddef.h>

/** 
 * @brief Create a barrier object for synchronization between threads.
 * @author Ido Naveh idonovo@gmail.com
 */ 


typedef struct Barrier Barrier;

/**  
 * @brief Afunction to create a barrier object.  
 * @param[in] _capacity - argument specifies the number of threads that must call pthread_barrier_wait() before any of them successfully return from the call.
 * @return Barrier* - on success
 * @retval NULL on fail 
 *
 */
Barrier* BarrierCreate(size_t _capacity);

/**  
 * @brief Afunction to destroy a barrier object. When the function is called it will wait until there are no remaining threads in the _barrier. 
 * @param[in] _barrier to destroy.
 *
 */
void BarrierDestroy(Barrier* _barrier);

/**  
 * @brief  a function to synchronize participating threads at the barrier referenced by _barrier. The calling thread shall block until the required number of threads have called BarrierWait.
 * @param[in] _barrier object for referance. 
 * @return -1 for ERROR / 0 on success/ 1 when exiting the function due to BarrierDestroy calling.
 *
 */
int BarrierWait(Barrier* _barrier);

