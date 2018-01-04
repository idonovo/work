
#include <vector>
#include "tContainer.h"
#include "tContainer_t1.h"

int main (int argc, char const* argv[])
{
	tContainer_t<int, list<int*>> x;
	cout<< x.IsEmpty() << endl;
	int* y = new int;
	*y = 3;
	x.Insert(y);
	int* z = new int;
	*z = 10;
	x.Insert(z);
	int* a = new int;
	*a = 7;
	x.Insert(a);
	int* t = x.Find(*z);
	cout << *t << endl;
	//*t =  x[6];
	
	tContainer_t1<int, vector> b;
	
	return 0;
}

