#include "stdafx.h"
#include "TaskHandler.h"
//#include <iostream>

namespace advcpp
{

/*****************************static members*************************/
/*******************************************************************/

bool TaskHandler::m_pauseExecution = false;
Condition_variable TaskHandler::pauseCond;
Mutex TaskHandler::m_mutex;

/*****************************static mfunctions*************************/
/*******************************************************************/

void TaskHandler:: PuaseExecution()
{
	TaskHandler::m_pauseExecution = true;
}

void TaskHandler:: ContinueExecution()
{
	TaskHandler::m_pauseExecution = false;
	pauseCond.Notify_all();
	//std::cout << "open" << std::endl;
}
/*******************************************************************/
TaskHandler::TaskHandler (PriorityQueue< std::tr1::shared_ptr<Task>, std::vector<std::tr1::shared_ptr<Task> >, Task::Less >& x): m_stopExecution(false), m_queue(x), m_thread(this){} 

TaskHandler::~TaskHandler (){}
    
void TaskHandler::Run()
{
	while(!m_stopExecution)
	{
		while(m_pauseExecution)
		{
			Guard gaurd(m_mutex);
			//std::cout << "puase" << std::endl;
			pauseCond.Wait(m_mutex);
			//std::cout << "out" << std::endl;
		}
		std::tr1::shared_ptr<Task> t = m_queue.TopAndPop();
		try{
		    t->OnTask();
		}catch(...)
		{
		    throw std::runtime_error("Bad Task"); //deal with errors
		}
		
	}
}

void TaskHandler:: ExitExecution()
{
	m_thread.Join();
}

void TaskHandler:: StopExecution()
{
	m_stopExecution = true;
}

#ifdef __linux__	
void TaskHandler::CancelExecution()
{
	m_thread.Cancel();
}
#endif

}

