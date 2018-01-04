#ifndef __UI__
#define __UI__

#include "queryProtocol.h"


/** 
 * @brief * function to print data of single subscriber.
 * 
 * @param[in] _adt -SubscribersADT* container.
 * @param[in] _query- adt with subscriber key identefier.
 */
void SubscriberQuery(SubscribersADT* _adt, Query* _query); 

/** 
 * @brief * function to print data of single operator.
 * 
 * @param[in] _adt -OperatorsADT* container.
 * @param[in] _query- adt with operator key identefier.
 */
void OperatorQuery(OperatorsADT* _adt, Query* _query);

/** 
 * @brief * function to print data of all subscriber to file
 * 
 * @param[in] _adt -SubscribersADT* container.
 * @param[in] _query- adt with file path.
 * @returns 0 on success/ -1 on failure.
 */
int AllSubscribersReport(SubscribersADT* _adt, Query* _query); 

/** 
 * @brief * function to print data of all operators to file
 * 
 * @param[in] _adt -OperatorsADT* container.
 * @param[in] _query- adt with file path.
 * @returns 0 on success/ -1 on failure.
 */
int AllOperatorsReport(OperatorsADT* _adt, Query* _query);

/** 
 * @brief * function to print data of all operators and operators to file
 * 
 * @param[in] _adtSubs -SubscribersADT* container.
 * @param[in] _adtOpts -OperatorsADT* container.
 * @param[in] _query- adt with file path.
 * @returns 0 on success/ -1 on failure.
 */
int AggregateReport(SubscribersADT* _adtSubs, OperatorsADT* _adtOpts, Query* _query);    

#endif
