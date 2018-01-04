#include "shared.h"


void Add(int num)
{
	cout << num +num << endl;	
}


void Mult(int num)
{
	cout << num  * num << endl;	
}

void AddAndMult(int num)
{
	cout << num  * num  + num << endl;	
}

Foot FindFunc(const string& name)
{
	if(name == "Add")
	{
		return Add;
	}
	
	if(name == "Mult")
	{
		return Mult;
	}
	
	if(name == "AddAndMult")
	{
		return AddAndMult;
	}
	return AddAndMult;
}



