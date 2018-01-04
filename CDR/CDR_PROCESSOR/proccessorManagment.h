

#include "protocol.h"
#include "storeSubData.h"
#include "storeOptData.h"
#include "TransmissionData.h"
#include "../../inc/logger.h"
#include "../../inc/config.h"
#include "dealQuery.h"
#include "queryProtocol.h"


#define PATH_SIZE 64

typedef struct ProcessorConfig
{
	char 		m_feederPath[PATH_SIZE];
	char		m_feederKey;
	char 		m_feederType;
	char 		m_queryPath[PATH_SIZE];
	char		m_queryKey;
	char 		m_queryType;
	size_t 		m_size;
}ProcessorConfig;

typedef struct ManagmentData
{
	ChannelData* 		m_feedrChannelData;
	ChannelData* 		m_queryChannelData;
	SubscribersADT* 	m_subscribersADT;
	OperatorsADT*		m_operatorsADT;
	int 				m_shutDown;
}ManagmentData;

/** 
 * @brief * function to create processor ADT's.
 * 
 * @param[in] _processorConfigFileName - path for configuration file for the processor module.
 * @returns ManagmentData* / NULL if error occured.
 */
ManagmentData* CreateManagmentData(char* _processorConfigFileName);


int ManagerRoutine(char* _configFile);

/** 
 * @brief * processing routine function. the basic flow is to get cdr record using transmission modul and deliver the record to the sub/op adt's moduls.
 * 
 * @param[in] _managmentData - ManagmentData* with acc to all other moduls ADT's.
 * @returns  0 on success / -1 on failure.
 */
void* ProcessingRoutine(void* _context);

/** 
 * @brief * query routine function. the basic flow is to get query from UI using transmission modul and respond using the sub/op adt's moduls.
 * 
 * @param[in] _managmentData - ManagmentData* with acc to all other moduls ADT's.
 * @returns  0 on success / -1 on failure.
 */
void* QueryRoutine(void* _context);    

/* destroy function */
void DestroyManagmentData(ManagmentData* _managmentData);









