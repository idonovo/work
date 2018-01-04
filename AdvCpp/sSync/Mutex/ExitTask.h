#ifndef __MYEMPTYTASK_H__
#define __MYEMPTYTASK_H__

#include <sys/types.h>
#include <iostream>
#include "Task.h"

namespace advcpp
{
class ExitTask: public Task
{
public:
	ExitTask(std::size_t priority = -1):Task( priority){}
	~ExitTask(){}
	void OnTask() { std::cout<< "Exit task for Thread"  << std::endl;}
};


}
#endif /* __MYEMPTYTASK_H__ */

