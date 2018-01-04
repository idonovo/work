#ifndef __MYTASKORG_H__
#define __MYTASKORG_H__

#ifdef __linux__	
#include <tr1/memory>
	#elif WIN32
#include <memory>		
#endif

#include "PriorityQueue.h"
#include "Task.h"
#include "Thread.h"
#include "Mutex.h"
#include "Guard.h"
//#include "ThreadPool.h"

namespace advcpp
{


class TaskHandler
{
public:
    TaskHandler (PriorityQueue< std::tr1::shared_ptr<Task>, std::vector<std::tr1::shared_ptr<Task> >, Task::Less >&);
    virtual ~TaskHandler();
    
    virtual void Run();
#ifdef __linux__	
    void	CancelExecution();
#endif
    void    StopExecution();
    void 	ExitExecution();
    
    static  void	PuaseExecution();
    static  void	ContinueExecution();
    
private:
    TaskHandler (const TaskHandler&);
    TaskHandler& operator=(const TaskHandler&); 

protected:    
    static 	Condition_variable pauseCond;
    static 	Mutex m_mutex;
    static	bool 	m_pauseExecution;
   
    bool m_stopExecution;
    PriorityQueue< std::tr1::shared_ptr<Task>, std::vector<std::tr1::shared_ptr<Task> >, Task::Less >& m_queue;
    Thread<TaskHandler> m_thread;
};

}

#endif /* __MYTASKORG_H__ */

