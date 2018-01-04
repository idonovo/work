
#include "Observer.h"
#include "Subject.h"

Observer::~Observer ()
{
	if(sbj)
	{
		sbj->Detach(this, whoAmI);
	}
}

Observer:: Observer(Subject* _sbj, const string& _type)
{
	if(_sbj)
	{
		sbj = _sbj;
		whoAmI = _type;
		sbj->Attach(this, whoAmI);
	}
}
