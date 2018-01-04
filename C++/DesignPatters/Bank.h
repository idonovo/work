#ifndef __MYBANK_H__
#define __MYBANK_H__

#include "Subject.h"

#include <iostream>
using namespace std;

class Bank: public Subject
{

public:
	static Bank& CreateBank(){return bank;}
	virtual ~Bank (){};
	
	void Destroy();
    bool OpenAccount(const string& _type);
    void GiveBonus();
    void Invest();
    void Meeting();
    virtual void Notify(const string& _whoAmI);
    
private:
	static Bank bank;
	
private:
    Bank(){}
	Bank (const Bank& arguments);
    Bank&operator=(const Bank& arguments);

};


#endif /* __MYBANK_H__ */



