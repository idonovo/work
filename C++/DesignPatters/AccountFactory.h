#ifndef __ACCOUNT_FACTORY_H__
#define __ACCOUNT_FACTORY_H__


#include <string>
#include "AccountImp.h"
#include "SingleAccount.h"


class Account;
using namespace std;


class AccountFactory
{
public:
    static AccountImp* Create(const string& _type)
    {
        AccountImp* account = 0;
        if(_type == "Family")
        {
            account = new FamilyAccount;
        }
        else if(_type == "Personal")
        {
            account = new PersonalAccount;
        }
        else if(_type == "Stock")
        {
            account = new StockAccount;
        }
        return account;
  
    }
    
    static void Destroy(AccountImp* _account)
    {
        delete _account;
    }

private:
    AccountFactory();
    AccountFactory(const AccountFactory&);
    AccountFactory& operator=(const AccountFactory&);
};

#endif /* __ACCOUNT_FACTORY_H__ */

