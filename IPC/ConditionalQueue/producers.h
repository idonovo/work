
#include "queue.h"

typedef struct Producers Producers;

typedef struct Input Input;

typedef struct ProducersContext ProducersContext;

struct Input
{
	size_t m_numOfCycls, m_numOfProducers, m_numOfConsumers, m_queueSize;
};

/******************************************************************/

void ParseInput(Input* _input, int argc, char **argv);

Producers* CreateProducers(size_t _numOfProducers, size_t _numOfCycels);

int ExecuteProducerThreads(Producers* _producers, void* _context);

void* CreateProducerContext(Queue* _questionsQueue, Queue* _answersQueue, size_t _numOfCycels);

void ProducersJoin(const Producers* _producers);

void DestroyProducersData(Producers* _producers, void* _context);


