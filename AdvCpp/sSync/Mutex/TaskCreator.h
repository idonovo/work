#ifndef __TEMPLATETASK_H__
#define __TEMPLATETASK_H__

#include "Task.h"

namespace advcpp
{

template <class T>
class TaskCreator: public Task
{
public:
	TaskCreator(std::tr1::shared_ptr<T> , std::size_t _priority = 1);
	virtual ~TaskCreator ();
	virtual void OnTask(); 

private:
	std::tr1::shared_ptr<T> m_obj;
};

template <class T>
TaskCreator<T>::TaskCreator(std::tr1::shared_ptr<T> _obj, std::size_t _priority): Task( _priority), m_obj(_obj){}

template <class T>
TaskCreator<T>::~TaskCreator(){}

template <class T>
void TaskCreator<T>::OnTask()
{
	 m_obj->OnTask();
}

}



#endif /* __TEMPLATETASK_H__ */

