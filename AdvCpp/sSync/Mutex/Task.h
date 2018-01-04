#ifndef __RUNABLE_H__
#define __RUNABLE_H__

#ifdef __linux__	
#include <tr1/memory>
	#elif WIN32
#include <memory>		
#endif

#include <cstddef>

namespace advcpp
{


class Task
{
public:
    Task(std::size_t _priority);
    virtual ~Task();
    Task(const Task&);
    Task& operator=(const Task&);
    
    
    bool operator< (const Task& _task) const; 
    virtual void OnTask() = 0; 
    std::size_t  GetPriority()const;
    
    class Less
    {
    public:
    	Less(){}
    	bool operator()(std::tr1::shared_ptr<Task> _task1, std::tr1::shared_ptr<Task> _task2)const;
    }; 
private:
    std::size_t m_priority;
};

} //namespace

#endif /* __RUNABLE_H__ */

