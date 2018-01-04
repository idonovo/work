#ifndef __CLEANUPHANDLER_H__
#define __CLEANUPHANDLER_H__

#include "TaskHandler.h"

namespace advcpp
{

class CleanUpHandler: public TaskHandler
{
public:
	CleanUpHandler (PriorityQueue< std::tr1::shared_ptr<Task>, std::vector<std::tr1::shared_ptr<Task> >, Task::Less >&);
	virtual ~CleanUpHandler ();
    virtual void    Run(); 

private:
    CleanUpHandler (const CleanUpHandler&);
    CleanUpHandler& operator=(const CleanUpHandler&);

};

}

#endif /* __CLEANUPHANDLER_H__ */

