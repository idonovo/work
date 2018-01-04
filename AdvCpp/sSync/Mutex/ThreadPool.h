#ifndef __MYTHREADPOOL_H__
#define __MYTHREADPOOL_H__

#ifdef __linux__	
#include <tr1/memory>
	#elif WIN32
#include <memory>		
#endif

#include "TaskCreator.h"
#include "PriorityQueue.h"
#include "Task.h"
#include "TaskHandler.h"
#include "Thread.h"
#include "Mutex.h"

namespace advcpp
{

class ThreadPool
{
public:
    const static std::size_t DEFAULT_NUM_OF_TREADS;
private:
	static void StopHandler(std::tr1::shared_ptr<TaskHandler>& _handler);
	static void CallToExit(std::tr1::shared_ptr<TaskHandler>&);
	static void CallToCancel(std::tr1::shared_ptr<TaskHandler>&);
    
public:
    explicit ThreadPool();
    explicit ThreadPool(std::size_t _numOfThreads);
    ~ThreadPool();
    
    ThreadPool (const ThreadPool&);
    ThreadPool& operator=(const ThreadPool&);
    
    template<class T>
    void AddTask(std::tr1::shared_ptr<T> , std::size_t _priority);
    
    void ResizePool(int);
    std::size_t GetSize()const;
    void FullGracefulShutDown();
    void GracefulShutDown();
    void ImmediateShutDown();
    
    void PauseExecution();
    void ContinueExecution();

private:    
	void 	IncreasePool(std::size_t);
	void 	DecreasePool(std::size_t);
	void 	SendReleaseTasks(std::size_t);
	void 	CleanUp();

    bool m_isSafeToExit;
    bool m_canAddTasks;
    std::size_t m_numOfThreads;
    mutable Mutex   m_mutex;
    PriorityQueue< std::tr1::shared_ptr<Task>, std::vector<std::tr1::shared_ptr<Task> >, Task::Less > m_queue;
    std::vector<std::tr1::shared_ptr<TaskHandler> > m_vec;
};

template<class T>
void  ThreadPool::AddTask(std::tr1::shared_ptr<T> _obj, std::size_t _priority)
{
	if(m_canAddTasks)
	{
		std::tr1::shared_ptr<Task> newtask(new TaskCreator<T>(_obj, _priority));
		m_queue.Push(newtask);
	}
}


}

#endif /* __MYTHREADPOOL_H__ */

