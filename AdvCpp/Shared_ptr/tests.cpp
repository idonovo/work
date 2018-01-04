#include "mu_test.h"
#include "Shared_ptr.h"
#include <iostream>
#include <vector>
#include <unistd.h>
#include <pthread.h>


using namespace advcpp;

class dog
{
public:	
	int bark;
	int sniff;
	dog(int x, int y): bark(x), sniff(y){}
};

void* CreadHundredPtr(Shared_Ptr<int>* _a)
{
    std::vector< Shared_Ptr<int> > ptrs;
    for(unsigned int i = 0; i < 1000; ++i)
    {
        ptrs.push_back(*_a);
    }
    
    pause();
    
    return 0;
}

void* assignHundredPtr(Shared_Ptr<int>* _a)
{
    std::vector< Shared_Ptr<int> > ptrs;
    for(unsigned int i = 0; i < 1000; ++i)
    {
        ptrs.push_back(*_a);
    }
    
    pause();
    
    return 0;
}

UNIT(COPY_CTOR)
{
    Shared_Ptr<int> ptr(new int(1));
    pthread_t* threads = new pthread_t[100];
    for(unsigned int i = 0; i < 100; ++i)
    {
        pthread_create(threads + i, 0, (void * (*)(void *))CreadHundredPtr, &ptr);
    }
    
    sleep(2);
    
    ASSERT_THAT(100001 == ptr.GetCounter());
    
    for(unsigned int i = 0; i < 100; ++i)
    {
        pthread_cancel(threads[i]);
        pthread_join(threads[i], 0);
    }
    
    ASSERT_THAT(1 == ptr.GetCounter());
}
END_UNIT

UNIT(DefaultCtor)
{
	Shared_Ptr<int> sharedPtr;
	sharedPtr = new int(7);
	ASSERT_THAT(true);
}
END_UNIT

UNIT(NormalCtor)
{
	int* ptr = new int(7);
	Shared_Ptr<int> sharedPtr(ptr);
	
	ASSERT_THAT(sharedPtr.GetPtr() == ptr);
	ASSERT_THAT(sharedPtr.GetCounter() == 1);
}
END_UNIT

UNIT(CopyCtor)
{
	Shared_Ptr<int> sharedPtr(new int(7));
	
	{
		Shared_Ptr<int> secondPtr = sharedPtr;
		ASSERT_THAT(sharedPtr.GetPtr() == secondPtr.GetPtr());
		ASSERT_THAT(sharedPtr.GetCounter() == 2);
	}
	
	ASSERT_THAT(sharedPtr.GetCounter() == 1);
}
END_UNIT

UNIT(Assignment)
{
	Shared_Ptr<int> firstPtr;
	{
		Shared_Ptr<int> secondPtr(new int(7));
		firstPtr = secondPtr;
		ASSERT_THAT(secondPtr.GetPtr() == firstPtr.GetPtr());
		ASSERT_THAT(firstPtr.GetCounter() == 2);
		ASSERT_THAT(secondPtr.GetCounter() == 2);
		{
			Shared_Ptr<int> thirdPtr;
			thirdPtr = secondPtr;
			ASSERT_THAT(firstPtr.GetPtr() == thirdPtr.GetPtr());
			ASSERT_THAT(thirdPtr.GetCounter() == 3);
		}
		ASSERT_THAT(secondPtr.GetCounter() == 2);
		ASSERT_THAT(firstPtr.GetCounter() == 2);
	}
	ASSERT_THAT(firstPtr.GetCounter() == 1);
}
END_UNIT

UNIT(cond)
{
	Shared_Ptr<int> secondPtr(new int(7));
	ASSERT_THAT(secondPtr);
		
}
END_UNIT

UNIT(Dereference)
{
	Shared_Ptr<int> sharedPtr(new int(7));
	Shared_Ptr<int> secondPtr = sharedPtr;
	
	ASSERT_THAT(*sharedPtr == 7);
	ASSERT_THAT(*secondPtr == 7);
	
}
END_UNIT

class Person
{
public:
	Person() : m_age(7) {}
	int m_age;
};

class Ido: public Person
{
public:
	Ido() : Person(), my_age(32) {}
	int my_age;
};

UNIT(Arrow)
{
	
	Shared_Ptr<Person> sharedPtr(new Person);
	Shared_Ptr<Person> secondPtr = sharedPtr;
	
	ASSERT_THAT(sharedPtr->m_age == 7);
	ASSERT_THAT(secondPtr->m_age == 7);
}
END_UNIT

UNIT(Inheritence)
{	
	Shared_Ptr<Ido> secondPtr(new Ido);
	Shared_Ptr<Person> sharedPtr(secondPtr);
	
	ASSERT_THAT(sharedPtr->m_age == 7);
}
END_UNIT

UNIT(BOOL)
{	
	Shared_Ptr<Ido> secondPtr(new Ido);
	ASSERT_THAT(!!secondPtr);
}
END_UNIT

TEST_SUITE(sharedPtr)
	TEST(COPY_CTOR)
	TEST(DefaultCtor)
	TEST(NormalCtor)
	TEST(CopyCtor)
	TEST(Assignment)
	TEST(Dereference)
	TEST(Arrow)
	TEST(cond)
	TEST(Inheritence)
	TEST(BOOL)
END_SUITE
