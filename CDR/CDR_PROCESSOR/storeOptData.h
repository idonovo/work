
#ifndef __STORE_OPDATA__
#define __STORE_OPDATA__


#include "protocol.h"
/* a mudul to save CDR records in operator and subscribers adt's (currently hashMap)). flow: the first thread will create two atd's with capacity . next threads after recivieng CdrData record will use this api to store the records in the adt's.  */

typedef struct CdrData CdrData;

typedef struct OperatorsADT OperatorsADT;

typedef struct Operator Operator;

/** 
 * @brief * function to create Operators ADT container .
 * 
 * @param[in] _size - capacity of  the container.
 * @param[in] _logData- logger to print actions,
 * @returns OperatorsADT* / NULL if error occured.
 */

OperatorsADT* CreateOperatorsADT(size_t _size, LogData* _logData);

/** 
 * @brief * function to insert cdr record of single subscriber of oerator to container . if the operator is not exist the container will create new operator object.
 * 
 * @param[in] _adt - SubscribersADT* to insert data.
 * @param[in] _data- Cdr record to insert.
 * @returns o on success / -1 on failure.
 */
int InsertToOperatorsADT(OperatorsADT* _adt, CdrData* _data);

/* function to destroy SubscribersADT*/ 
void DestroyOperatorsADT(OperatorsADT* _adt);

#endif
