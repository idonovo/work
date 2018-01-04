#include "Singleton.h"
#include <iostream>
#include <unistd.h> // sleep
#include <sys/types.h>

using namespace advcpp;

class Dog
{

friend  std::tr1::shared_ptr<Dog> Singleton<Dog>::GetInstance(); 

public:
	static unsigned int idogs;
	unsigned int thisDog;
	
private:
	Dog ()
	{	
		thisDog = ++idogs;
		
		// working .. 
		sleep(1);
		
		std::cout << "dog no. " << thisDog << "constructed\n";
	}
};	
	

void* CreateDog(void* _context)
{
	for (unsigned int i = 0; i < 10; i += 1)
	{
		std::tr1::shared_ptr<Dog> dog = Singleton<Dog>::GetInstance();
		std::cout << "thread  number: "<< pthread_self() <<"got dog " << dog->thisDog << std::endl;
	}
}

unsigned int Dog::idogs = 0;

int main (int argc, char const* argv[])
{
	const unsigned int nThreads = 10000;
	
	pthread_t threads[nThreads];
	
	for (unsigned int i = 0; i < nThreads; i += 1)
	{
		while (pthread_create(threads + i, NULL, CreateDog, NULL))
		{
			pthread_join(threads[i-1], NULL);
		}
	}	
	
	for (unsigned int i = 0; i < nThreads; i += 1)
	{
		pthread_join(threads[i], NULL);
	}
			
}

