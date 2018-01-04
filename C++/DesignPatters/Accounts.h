#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

#include "Observer.h"

#include <iostream>
using namespace std;

class AccountImp;

class Account: public Observer
{

public:
     Account(Subject* _subj, const string& _accType); 
    
	virtual ~Account ();
    virtual void Update(Subject* _sbj);
    
private:
	Account (const Account& arguments);
    Account&operator=(const Account& arguments);

private:
	AccountImp* m_imp; 
	string m_type;
};

#endif /* __ACCOUNT_H__ */

