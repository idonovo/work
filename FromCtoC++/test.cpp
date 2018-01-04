
#include <iostream>
using namespace std;
	
class Ido
{
	public:
	virtual void foo(){cout << "ido" << endl;}
};

class Shai : public Ido
{
	public:
	void foo(){cout << "shai" << endl;}
};

int main (int argc, char const* argv[])
{
	
	Shai shai;
	Ido& ido = shai;
	ido.foo();
	return 0;
}
