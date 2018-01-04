#include "stdafx.h"
#include "Task.h"

namespace advcpp
{

Task::Task(std::size_t _priority):m_priority(_priority){}

Task:: ~Task(){}

bool Task::operator<(const Task& _task) const
{
	    return m_priority < _task.m_priority;
}

bool Task::Less::operator()(std::tr1::shared_ptr<Task> _task1, std::tr1::shared_ptr<Task> _task2) const
{
	return *_task1 < *_task2;
}

std::size_t Task::GetPriority()const
{
	return m_priority;
}


}

