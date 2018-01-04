#include "Accounts.h"
#include "AccountImp.h"
#include "AccountFactory.h"
#include "Observer.h"

Account::Account(Subject* _subj, const string& _accType):Observer((Subject*)_subj, _accType)
{
    m_type = _accType;
    m_imp = AccountFactory::Create(m_type);
    if(!m_imp)
    {
        throw("Failed");
    }
}
    
Account::~Account ()
{
	delete m_imp;
	m_imp = 0;
}

void Account::Update(Subject* _sbj)
{
	if(_sbj)
	{
		m_imp->DoUpdate();
	}
}

