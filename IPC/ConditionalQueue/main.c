
#include "queue.h"
#include "producers.h"
#include "consumer.h"


int main (int argc, char **argv)
{
	Queue* questionsQueue;
	Queue* answersQueue;
	Consumers* consumers;
	Producers* producers;
	void* consumerContext;
	void* producerContext;
	Input input;
	
	ParseInput(&input, argc, argv);

	questionsQueue = QueueCreate(input.m_queueSize);
	answersQueue = QueueCreate(input.m_queueSize);
	
	consumers = CreateConsumers(input.m_numOfConsumers);
	producers = CreateProducers(input.m_numOfProducers, input.m_numOfCycls);
	
	consumerContext = CreateConsumersContext(questionsQueue, answersQueue);
	producerContext = CreateProducerContext(questionsQueue, answersQueue,  input.m_numOfCycls);
	
	ExecuteConsumerThreads(consumers, consumerContext);
	ExecuteProducerThreads(producers, producerContext);
	
	ConsumersJoin(consumers);
	ProducersJoin(producers);
	
	DestroyConsumerContextData(consumers, consumerContext);
	DestroyProducersData(producers, producerContext);
	QueueDestroy(questionsQueue);
	QueueDestroy(answersQueue);
	
	return 0;
	
}

