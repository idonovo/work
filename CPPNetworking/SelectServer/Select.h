#ifndef __MYSELECT_H__
#define __MYSELECT_H__

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstddef>
#include <tr1/memory>

#include "Selectable.h"

namespace Netcpp
{

class Select
{
public:
	
	const static std::size_t MAX_FD_T = 1024;
	
	Select ();
	virtual ~Select ();
	
	virtual void AddSelectable(std::tr1::shared_ptr<Selectable>);
	virtual void RemoveSelectable(std::tr1::shared_ptr<Selectable>);
	void ClearSet(void);
	std::size_t GetSetSize(void) const;
	bool IsSet(std::tr1::shared_ptr<Selectable>);
	
	std::size_t GetNumOfActiveSelectable();

private:

	Select(const Select&);
	Select& operator=(const Select&);

private:
	fd_set m_set;
};
}

#endif /* __MYSELECT_H__ */

