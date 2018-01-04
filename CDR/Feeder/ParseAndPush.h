#ifndef __PARSE___
#define __PARSE__

#include <stdio.h>

#include "protocol.h"
#include "fidders.h"

typedef struct CdrData CdrData; 

int Parse(char* _line, CdrData* _cdr);

void* ReadCdrFile(void* _context);

int NotifyCdrFile(FeedersContext* _context);

#endif

