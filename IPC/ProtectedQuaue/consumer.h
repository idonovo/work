
#include "queue.h"

typedef struct Consumers Consumers;

typedef struct ConsumersContext ConsumersContext;

Consumers* CreateConsumers(size_t _numOfConsumers);

int ExecuteConsumerThreads(void* _context);

void* CreateConsumersContext(Queue* _questionsQueue, Queue* _answersQueue, Consumers* _consumers);

void* ConsumerRoutine(void* _context);

int ConsumersJoin(const Consumers* _consumers, void* _context);

void DestroyConsumerContext(void* _context);

void SendExitMessage(ConsumersContext* _context);



