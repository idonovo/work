#include <iostream>

template<unsigned int N>
struct Fibbonaci
{
	static const unsigned long long fib = Fibbonaci<N-1>::fib  +  Fibbonaci<N-2>::fib;	
};

template<>
struct Fibbonaci <1>
{
	static const long long fib = 1;
};

template<>
struct Fibbonaci <0>
{
	static const long long fib = 0;
};


int main (int argc, char const* argv[])
{
	Fibbonaci<50> t;
	
	std::cout << t.fib << std::endl;
	return 0;
}


