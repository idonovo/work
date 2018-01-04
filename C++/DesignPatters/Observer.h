#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include <iostream>
using namespace std;

class Subject;

class Observer
{

public:
	virtual ~Observer ();
	virtual void	Update(Subject* _sbj) = 0;
	
protected:
    Observer(Subject*, const string&);
    Subject* sbj;
    string whoAmI;     

private:	
	Observer (const Observer& arguments);
    Observer&operator=(const Observer& arguments);

};




#endif /* __OBSERVER_H__ */

