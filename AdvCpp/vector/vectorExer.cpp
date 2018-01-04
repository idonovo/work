#include <list>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm> 

unsigned int myfunction(unsigned int i)
{
	static unsigned int sum;
	sum +=i;
	return sum;
}



struct Sum
{
   	public:
   	Sum():sum(0){}
   	void operator()(unsigned int val)
   	{
   		sum+=val; 
   	}
	int sum;
};   

int main (int argc, char const* argv[])
{
	
	std::set<int> vec;
	
	for (unsigned int i = 0; i < 10; i += 1)
	{
		vec.insert(i);
	}

	Sum s = for_each (vec.begin(), vec.end(), Sum());
	std::cout << s.sum << std::endl;
	
	unsigned int res = for_each (vec.begin(), vec.end(), myfunction)(res);
	std::cout << res << std::endl;
	return 0;
}

