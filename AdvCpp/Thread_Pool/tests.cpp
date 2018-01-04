#include "mu_test.h"
#include "ThreadPool.h"
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

using namespace advcpp;

class Con
{
	public:
	Con(PriorityQueue<int>& _t): queue(_t){}
	
	void Run()
	{
		
		for (int i = 0; i < 2500; i += 1)
		{
			int x;
			//usleep(100);
			x = queue.TopAndPop();
			std::cout << "removed number " << x << std::endl;
		}
	}
	PriorityQueue<int>& queue;
};


class Pro
{
	public:
	Pro(PriorityQueue<int>& _t): queue(_t){}
	
	void Run()
	{
		for (int i = 0; i <10000; i += 1)
		{
			queue.Push(i);
			std::cout << "inserted number " << i << std::endl;
		}
	}
	PriorityQueue<int>& queue;
};

UNIT(Create_Queue)
	PriorityQueue<int> t(5000);
	 
END_UNIT

UNIT(simple_pro_con_Queue)
	PriorityQueue<int> t(10000);
	Pro pro1(t);
	Con con1(t);
	Con con2(t);
	Con con3(t);
	Con con4(t);
	Thread<Con> thread2(&con1);
	Thread<Con> thread3(&con2);
	Thread<Con> thread4(&con3);
	Thread<Con> thread5(&con4);
	Thread<Pro> thread1(&pro1);
	thread1.Join();
	thread2.Join();
	thread3.Join();
	thread4.Join();
	thread5.Join();
END_UNIT	

UNIT(simple_Single_pro_con_Queue)
	PriorityQueue<int> t(10);
	Pro pro1(t);
	Con con1(t);
	Thread<Con> thread2(&con1);
	Thread<Pro> thread1(&pro1);
	thread1.Join();
	thread2.Join();
END_UNIT

int t = 0;
class SimpleTask: public Task
{
	public:
	SimpleTask(std::size_t priority):Task( priority){}
	virtual void OnTask()
	{
		std::cout<< pthread_self() << " on task " << GetPriority()<< "  " << std::endl;
	} 
};

UNIT(print_Queue)
	PriorityQueue< std::tr1::shared_ptr<Task>, std::vector<std::tr1::shared_ptr<Task> >, Task::Less > t; 
	for (unsigned int i = 0; i < 10; i += 1)
	{
		 std::tr1::shared_ptr<Task> q (new SimpleTask(rand() % 10 + 1));
		t.Push(q);
	}
	
	for (unsigned int i = 0; i < 10; i += 1)
	{
		std::tr1::shared_ptr<Task> q = t.TopAndPop();
		q->OnTask();
		std::cout<< q->GetPriority() << std::endl;
	}
END_UNIT

UNIT(create_pool)
	ThreadPool x(2000);
	//x.StopExecution();
END_UNIT

UNIT(add_pool)
	ThreadPool x(100);
	for (unsigned int i = 0; i < 10; i += 1)
	{
		for (unsigned int i = 0; i < 500; i += 1)
		{
			std::tr1::shared_ptr<SimpleTask> q (new SimpleTask(rand() % 10 + 1));
			x.AddTask<SimpleTask>(q, q->GetPriority());
		}
	}
	sleep(2)
END_UNIT


UNIT(stop_pool)
	ThreadPool x(100);
	for (unsigned int i = 0; i < 10; i += 1)
	{
		for (unsigned int i = 0; i < 500; i += 1)
		{
			std::tr1::shared_ptr<SimpleTask> q (new SimpleTask(rand() % 10 + 1));
			x.AddTask<SimpleTask>(q, q->GetPriority());
		}
	}
	x.GracefulShutDown();
	sleep(2)
END_UNIT

UNIT(pause_pool)
	ThreadPool x(2);
	x.PauseExecution();
	for (unsigned int i = 0; i < 2; i += 1)
	{
		std::tr1::shared_ptr<SimpleTask> q (new SimpleTask(rand() % 10 + 1));
		x.AddTask<SimpleTask>(q, q->GetPriority());
	}
	sleep(1);
	x.ContinueExecution();
	sleep(1);
	x.GracefulShutDown();
END_UNIT

UNIT(resize_pool)
	ThreadPool x(50);
	for (unsigned int i = 0; i < 200; i += 1)
	{
		std::tr1::shared_ptr<SimpleTask> q (new SimpleTask(rand() % 10 + 1));
		x.AddTask<SimpleTask>(q, q->GetPriority());
	}
	x.ResizePool(-27);
	sleep(1);
	ASSERT_THAT(x.GetSize() == 23);
	x.GracefulShutDown();
END_UNIT

UNIT(immi_stop_pool)
	ThreadPool x(2);
	for (unsigned int i = 0; i < 200; i += 1)
	{
		std::tr1::shared_ptr<SimpleTask> q (new SimpleTask(rand() % 10 + 1));
		x.AddTask<SimpleTask>(q, q->GetPriority());
	}
	x.ImmediateShutDown();
END_UNIT

UNIT(full_grace_stop_pool)
	ThreadPool x(10);
	for (unsigned int i = 0; i < 3000; i += 1)
	{
		std::tr1::shared_ptr<SimpleTask> q (new SimpleTask(rand() % 10 + 1));
		x.AddTask<SimpleTask>(q, q->GetPriority());
	}
	x.FullGracefulShutDown();
	ASSERT_THAT(x.GetSize() == 1);
END_UNIT


TEST_SUITE(Thread_Pool)
//	TEST(Create_Queue)
//	TEST(simple_pro_con_Queue)
//	TEST(simple_Single_pro_con_Queue)
//	TEST(create_pool)
//	TEST(print_Queue)
//	TEST(add_pool)
	TEST(stop_pool)
	TEST(pause_pool)
	TEST(resize_pool)
	TEST(full_grace_stop_pool)
	TEST(immi_stop_pool)
END_SUITE

