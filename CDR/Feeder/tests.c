
#include <stdio.h>
#include "ParseAndPush.h"
#include "protocol.h"
#include "fidders.h"
#include "TransmissionData.h"
#include "../../inc/logger.h"
#include "../../inc/config.h"

#define CONF_FILE "Conf.txt"
#define PATH "/home/student/work/CDR/Feeder"
#define KEY 'f'
#define TYPE 1

void CdrGenerator(int _size)
{       
    size_t i;
    FILE* fp;
    char type[6] = "MOC";
    char imsi[16];
    
    
    fp = fopen("cdr.txt", "w");
    
    for(i=0; i< _size; ++i)
    {
        sprintf(imsi, "12312313%d", i);
        fprintf(fp, "%s | %s | %s |%s | %d | %s | %s | %s | %d | %d | %d | %s | %d |\n", imsi, imsi, "12345678901", "cellcom", 12345, type, "12/12/12", "11/11/11", 12 *i, 10 - i, 12+i, "124142463", imsi);
    }
    fclose(fp);
    return;
}

int main()
{
	CdrGenerator(10000);
	FeedersContext* feeder = CreateFiddersContext(NULL);
    ExecuteFiddersThreads(feeder);

    return 0;
}


