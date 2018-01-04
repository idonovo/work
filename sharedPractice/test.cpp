
#include <dlfcn.h>
#include <iostream>
#include "shared.h"



//extern "C"
typedef void(*Foot)(int);
typedef Foot (*Find)(const string& name);

int main (int argc, char const* argv[])
{
	//void  *handle  = 0;

	//handle = dlopen("./shared.so", RTLD_NOW | RTLD_GLOBAL);
	
	
	void  *handle = dlopen("./shared.so", RTLD_LAZY);
	if(!handle)
	{
		std::cout << "FAIL!!!";
	}
  	Find foo = (Find)dlsym(handle, "FindFunc");
  	
	Foot y = foo("Mult");
	y(7);
	y = foo("Add");
	y(100);
	//Foot();
	return 0;
}


