#include "SemGuard.h"

namespace advcpp
{

SemGuard::SemGuard(ISemaphore& _sem): m_sem(_sem)
{
	m_sem.Wait();
}

SemGuard::~SemGuard()
{
	m_sem.Post();
}	

}

