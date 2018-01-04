
#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "protocol.h"
#include "../../inc/logger.h"
#include "../../inc/config.h"

typedef struct ChannelData ChannelData;
/*************************************************************************/

/** 
 * @brief * function  to establashe communication channel between processor and feeder. if the communication channel already established the function will connect the proccess to it.
 * 
 * @param[in] _feederPath - path for directory.
 * @param[in] _feederKey - key which both feeder and processor will use for establish communication.
 * @returns Channel Data adt for continues communication/ NULL if error occured.
 */
ChannelData* CreateTransmissionChannel(char* _feederPath, char _feederKey, int _type, LogData* _log);

/** 
 * @brief * function to push generic data into communication channel
 * 
 * @param[in]  _context - data to push to the channel.
 * @param[in] _size - size in bytes of the _context.
 * @param[in] _data - Channel Data adt for continues communication.
 * @returns 0 for succes/ -1 if error occured.
 */
int PushToChannel(void* _context, size_t _size, ChannelData* _data);

/** 
 * @brief * function to read generic data from communication channel
 * 
 * @param[in]  _context - container to recieve data from the channel.
 * @param[in] _size - size in bytes of the _context.
 * @param[in] _data - Channel Data adt for continues communication.
 * @returns 0 for succes/ -1 if error occured/ 1 if last message rcivied.
 */

int ReadFromChannel(void* _context, size_t _size, ChannelData* _data);

/** 
 * @brief * function to signle last message into communication channel
 * 
 * @param[in] _data - Channel Data adt for continues communication.
 * @returns 0 for succes/ -1 if error occured.
 */
int SendLastMessage(ChannelData* _data);

/* @brief : function to close communication channel and destroy ChannelData adt */
void DestroyChannel(ChannelData* _data); 

#endif




