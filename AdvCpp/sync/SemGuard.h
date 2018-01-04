#ifndef __MYSEMSemGuard_H__
#define __MYSEMSemGuard_H__

#include "ISemaphore.h"

namespace advcpp
{

class SemGuard
{
public:
    SemGuard(ISemaphore&);
	~SemGuard ();
        
private:
	SemGuard (const SemGuard& arguments);
    SemGuard&operator=(const SemGuard& arguments);
	
	ISemaphore&	m_sem;
};
} 

#endif /* __MYSEMSemGuard_H__ */

