#include "stdafx.h"
#include "ThreadPool.h"
#include "ExitTask.h"
#include "TaskCreator.h"
#include "CleanUpHandler.h"
#include <algorithm>

namespace advcpp
{

/*****************************static members********************************/
/**************************************************************************/
const std::size_t ThreadPool::DEFAULT_NUM_OF_TREADS = 10;

void ThreadPool::CallToExit(std::tr1::shared_ptr<TaskHandler>& _handler)
{
	_handler->ExitExecution();
}

#ifdef __linux__	
void ThreadPool::CallToCancel(std::tr1::shared_ptr<TaskHandler>& _handler)
{
	_handler->CancelExecution();
}
#endif

void ThreadPool::StopHandler(std::tr1::shared_ptr<TaskHandler>& _handler)
{
	_handler-> StopExecution();
}
/**************************************************************************/
/**************************************************************************/
ThreadPool::ThreadPool(): m_isSafeToExit(false), m_canAddTasks(true), m_numOfThreads(DEFAULT_NUM_OF_TREADS)
{
	IncreasePool(m_numOfThreads);
}

ThreadPool::ThreadPool(std::size_t _numOfThreads): m_isSafeToExit(false), m_canAddTasks(true), m_numOfThreads(_numOfThreads)
{
	IncreasePool(m_numOfThreads);
}
	
ThreadPool::~ThreadPool()
{
	if(!m_isSafeToExit)
	{
		std::abort();
	}
	m_vec.erase(m_vec.begin(),m_vec.end());
//	StopExecution();
}

void ThreadPool::ResizePool(int _num)
{
	_num > 0 ? IncreasePool(_num): DecreasePool(_num * -1);
	m_numOfThreads += _num;
}


void ThreadPool::IncreasePool(std::size_t _num)
{
	for (std::size_t i = 0; i < _num; i += 1)
	{
		std::tr1::shared_ptr<TaskHandler> newHandler(new TaskHandler(m_queue));
		m_vec.push_back(newHandler);
	}
}

void ThreadPool::DecreasePool(std::size_t _num)
{
	
	for_each (m_vec.begin(),  m_vec.begin() + _num, StopHandler);
	PauseExecution();
	ContinueExecution();
	for_each (m_vec.begin(), m_vec.begin() + _num, CallToExit);
	m_vec.erase(m_vec.begin(),m_vec.begin() + _num);
}

void  ThreadPool::GracefulShutDown()
{
	for_each (m_vec.begin(), m_vec.end(), StopHandler);
	SendReleaseTasks(m_numOfThreads);
	for_each (m_vec.begin(), m_vec.end(), CallToExit);
	m_isSafeToExit = true;
}

void  ThreadPool::FullGracefulShutDown()
{
	m_canAddTasks = false;
	GracefulShutDown();
	m_vec.erase(m_vec.begin(),m_vec.end());
	m_numOfThreads = 0;
	CleanUp();
}

#ifdef __linux__	
void ThreadPool::ImmediateShutDown()
{
	for_each (m_vec.begin(), m_vec.end(), CallToCancel);
	for_each (m_vec.begin(), m_vec.end(), CallToExit);
	m_isSafeToExit = true;
}
#endif

void ThreadPool::SendReleaseTasks(std::size_t _num)
{
	for (unsigned int i = 0; i < _num; i += 1)
	{
		m_queue.Push(std::tr1::shared_ptr<Task> (new ExitTask));
	}
}

std::size_t ThreadPool::GetSize()const
{
	return m_numOfThreads;
}

void ThreadPool::PauseExecution()
{
	TaskHandler::PuaseExecution();
	SendReleaseTasks(m_numOfThreads);
}

void ThreadPool::ContinueExecution()
{
	TaskHandler::ContinueExecution();
}

void ThreadPool::CleanUp()
{
	std::tr1::shared_ptr<TaskHandler> cleanUpHandler(new CleanUpHandler(m_queue));
	m_vec.push_back(cleanUpHandler);
	++m_numOfThreads;
	ThreadPool::CallToExit(m_vec[0]);
}

}

