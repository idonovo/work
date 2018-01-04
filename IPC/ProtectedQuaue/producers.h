
#include "queue.h"

typedef struct Producers Producers;

typedef struct ProducersContext ProducersContext;

Producers* CreateProducers(size_t _numOfProducers, size_t _numOfCycels);

int ExecuteProducerThreads(Producers* _producers, void* _context);

void* CreateProducerContext(Queue* _questionsQueue, Queue* _answersQueue, size_t _numOfCycels);

void ProducersJoin(const Producers* _producers, void* _context);

void DestroyProducersData(Producers* _producers, void* _context);


