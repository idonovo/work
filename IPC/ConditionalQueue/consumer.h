
#include "queue.h"

typedef struct Consumers Consumers;

typedef struct ConsumersContext ConsumersContext;

Consumers* CreateConsumers(size_t _numOfConsumers);

int ExecuteConsumerThreads(Consumers* _consumers, void* _context);

void* CreateConsumersContext(Queue* _questionsQueue, Queue* _answersQueue);

int ConsumersJoin(const Consumers* _consumers);

void DestroyConsumerContextData(Consumers* _consumers, void* _context);


