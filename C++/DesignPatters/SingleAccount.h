#ifndef __SINGLEACCOUNTS__
#define __SINGLEACCOUNTS__

#include "Subject.h"
#include "AccountImp.h"

#include <iostream>
using namespace std;

class PersonalAccount: public AccountImp
{

public:
	PersonalAccount (): AccountImp(){}
	virtual ~PersonalAccount (){}
    virtual void	DoUpdate(){cout << "personal account updated" << endl;}
    
private:
	PersonalAccount (const PersonalAccount& arguments);
    PersonalAccount&operator=(const PersonalAccount& arguments);
	
};

class FamilyAccount: public AccountImp
{

public:
	FamilyAccount (): AccountImp(){}
	virtual ~FamilyAccount (){}
    virtual void	DoUpdate(){cout << "family account updated" << endl;}
    
private:
	FamilyAccount (const FamilyAccount& arguments);
    FamilyAccount&operator=(const FamilyAccount& arguments);
	
};

class StockAccount: public AccountImp
{

public:
	StockAccount (): AccountImp(){}
	virtual ~StockAccount (){}
    virtual void	DoUpdate(){cout << "stock account updated" << endl;}
    
private:
	StockAccount (const StockAccount& arguments);
    StockAccount&operator=(const StockAccount& arguments);
	
};


#endif /* __NAME_H__ */

