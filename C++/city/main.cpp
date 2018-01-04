

#include "Building_t.h"
#include "Street_t.h"
#include <iostream>
using namespace std;


int main()
{
	int x = 10;
	int y = 20;
	Building_t<int> b(x);
	Building_t<int> c(y);
	cout << c.GetBuildingID() << endl;
	c=b;
	cout << c.GetBuildingID() << endl;
	
	char e = 'b';
	Street_t<char, int> a(e);
	a.AddBuilding(b);
	b = a.GetBuilding(c.GetBuildingID()) ;
	cout << b.GetBuildingID() << endl;
	
	
	return 0;
}
