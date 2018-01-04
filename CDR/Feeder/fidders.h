
#include "protocol.h"
#include "TransmissionData.h"
#include "../../inc/logger.h"
#include "../../inc/config.h"


typedef struct FeedersContext FeedersContext;


/*function to create fidders threads with static routine function and FiddersContext */
FeedersContext* CreateFiddersContext(char* _configFile);

/*function to create fidders threads with static routine function and FiddersContext */
int ExecuteFiddersThreads(FeedersContext* _context);

/*
void* FeederRoutine(void* _context);

void* Monitor(void* _context);

*/




