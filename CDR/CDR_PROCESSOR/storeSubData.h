
#ifndef __STORE_DATA__
#define __STORE_DATA__


#include "protocol.h"
#include "../../inc/logger.h"
#include "../../inc/config.h"

/* a mudul to save CDR records in operator and subscribers adt's (currently hashMap)). flow: the first thread will create two atd's with capacity . next threads after recivieng CdrData record will use this api to store the records in the adt's. */

typedef struct CdrData CdrData;

typedef struct SubscribersADT SubscribersADT;

typedef struct Subscriber Subscriber;

/** 
 * @brief * function to subscribers ADT container .
 * 
 * @param[in] _size - capacity of  the container.
 * @param[in] _logData- logger to print actions,
 * @returns SubscribersADT* / NULL if error occured.
 */
SubscribersADT* CreateSubscribersADT(size_t _size, LogData* _logData);

/** 
 * @brief * function to insert cdr record of single subscriber to container. if the subscriber is not exist the container will create new subscriber object.
 * 
 * @param[in] _adt - SubscribersADT* to insert data.
 * @param[in] _data- Cdr record to insert.
 * @returns o on success / -1 on failure.
 */
int InsertToSubscribersADT(SubscribersADT* _adt, CdrData* _data);

/* function to destroy SubscribersADT*/ 
void DestroySubscribersADT(SubscribersADT* _adt); 

#endif

