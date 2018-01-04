#ifndef __ACCOUNTIMP_H__
#define __ACCOUNTIMP_H__

#include <iostream>
using namespace std;

class Bank;

class AccountImp
{

public:
    AccountImp(){};
	virtual ~AccountImp (){};
	virtual void DoUpdate() =0;
    
private:
	AccountImp (const AccountImp& arguments);
    AccountImp&operator=(const AccountImp& );

};

#endif /* __ACCOUNTIMP_H__ */

