#include "Bank.h"
#include "Observer.h"
#include "Accounts.h"


Bank Bank:: bank;

void Bank::Notify(const string& _type)
{
   
	std::pair<multimap<string, Observer*>::iterator, multimap<string, Observer*>::iterator> ret = m_observers.equal_range(_type);
	for (std::multimap<string, Observer*>::iterator it=ret.first; it!=ret.second; ++it)
	{
		it->second->Update(this);
	}
}

void Bank::Destroy()
{
    DeleteAll();
}

void Bank::GiveBonus()
{
    Notify("Family");
}

void Bank::Invest()
{
    Notify("Stock");
}

void Bank::Meeting()
{
    Notify("Personal");
}

bool Bank::OpenAccount(const string& _type)
{
    try
    {
        new Account(this, _type); 
    }
    catch(const char* str)
    {
        std::cout << "Failed" << std::endl;
        return false;
    }
    
    
    return true;
}
