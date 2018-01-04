#include "Subject.h"
#include "Observer.h"

void Subject::Attach(Observer* _obs, const string& observerType)
{
	if(_obs)
	{
		 m_observers.insert(pair<string,Observer*>(observerType, _obs));
	}
}

void Subject::Detach(Observer* _obs, const string& observerType)
{
	if(_obs)
	{
		std::pair<multimap<string, Observer*>::iterator, multimap<string, Observer*>::iterator> ret = m_observers.equal_range(observerType);
		for (std::multimap<string, Observer*>::iterator it=ret.first; it!=ret.second; ++it)
		{
			if(it->second == _obs)
			{
				m_observers.erase (it); 
				return; 
			}
		}
	}
}

void Subject::DeleteAll()
{
    for(multimap<string, Observer*>::iterator it = m_observers.begin(); it != m_observers.end(); ++it)
    {
        delete it->second;
    }
}

