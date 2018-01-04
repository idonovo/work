#include <iostream>

template<unsigned int N>
struct Factorial
{
	static const unsigned int f = N * Factorial<N-1>::f;	
};

template<>
struct Factorial <0>
{
	static const unsigned int f = 1;
};


int main (int argc, char const* argv[])
{
	Factorial<30> t;
	
	std::cout << t.f;
	return 0;
}


