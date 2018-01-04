#ifndef __SUBJECT_H__
#define __SUBJECT_H__



#include <map>
#include <iostream>
using namespace std;

class Observer;

class Subject
{
public:
	virtual ~Subject() {}

    virtual void Attach(Observer*, const string&);
    virtual void Detach(Observer*, const string&);
    
    void DeleteAll();
    int GetNumOfAcc()const {return m_observers.size();}
    
protected:
	Subject() {}
	virtual void Notify(const string& messageType) = 0;
    multimap<string, Observer*> m_observers; 
};
#endif /* __NAME_H__ */

