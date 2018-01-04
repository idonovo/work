#ifndef __ISELECTABLE_H__
#define __ISELECTABLE_H__

#include "fd_t.h"

namespace Netcpp
{

class Selectable
{
	friend class Select;

private:
	virtual const fd_t& GetFD_t() const = 0;

};

}


#endif /* __ISELECTABLE_H__ */

