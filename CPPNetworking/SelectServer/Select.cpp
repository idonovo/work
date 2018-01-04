#include "Select.h"
#include <stdexcept>
#include <errno.h>
#include <string.h>

namespace Netcpp
{

Select::Select ()
{
	FD_ZERO(&m_set);
}

Select::~Select (){}

void Select::AddSelectable(std::tr1::shared_ptr<Selectable> _ptr)
{
	FD_SET(_ptr->GetFD_t(), &m_set);
}

void Select::RemoveSelectable(std::tr1::shared_ptr<Selectable> _ptr)
{
	FD_CLR(_ptr->GetFD_t(), &m_set);
}

void Select::ClearSet(void)
{
	FD_ZERO(&m_set);
}

std::size_t  Select::GetSetSize(void) const
{
	 std::size_t count = 0;
	 
	 for (unsigned int i = 3; i <  MAX_FD_T; i += 1)
	 {
	 	if(FD_ISSET(i, &m_set))
	 	{
		 	++count;
	 	}
	 }
	 return count;
}

std::size_t Select::GetNumOfActiveSelectable()
{

	fd_set tempSet = m_set;
	int activity;
	activity = select(MAX_FD_T, &tempSet, NULL , NULL , NULL);
	
	if (activity < 0)
	{
 		throw std::runtime_error(strerror(errno));
	}

	return (std::size_t)activity;
}

bool Select::IsSet(std::tr1::shared_ptr<Selectable> _ptr)
{

	return FD_ISSET(_ptr->GetFD_t(), &m_set);
}

}	


