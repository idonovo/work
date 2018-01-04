#include "stdafx.h"
#include "CleanUpHandler.h"

namespace advcpp
{


CleanUpHandler::CleanUpHandler (PriorityQueue< std::tr1::shared_ptr<Task>, std::vector<std::tr1::shared_ptr<Task> >, Task::Less >& _queue): TaskHandler(_queue){}

CleanUpHandler::~CleanUpHandler (){}

void CleanUpHandler::Run()
{
	std::tr1::shared_ptr<Task> t;
	while(m_queue.TryTopAndPop(&t))
	{
		try{
		    t->OnTask();
		}catch(...)
		{
		   throw std::runtime_error("Bad Task"); //deal with errors
		}
	}
} 


}

