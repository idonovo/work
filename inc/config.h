#ifndef __CONFIG__
#define __CONFIG__

/** 
 *  @file config.h
 *  @brief basic functions to create a logger that load basic info of each function in a program to a file. the logger will close itself once the program will end.
	 *  
 *  @author Ido Naveh idonovo@gmail.com
 */

#include <stdio.h>
#include "logger.h"

typedef struct ConfigData
{
	char	m_logFileName[32];
	char	m_modulName[32];  
	char	m_level; 
}ConfigData;

/** 
 * 
 * @brief a function to wrute on an exist log  basic info of a function in a program.
 * @param[in] _logData : ADT to hold logger info.
 * @param[in] _funcName : function name
 * @param[in] _line, : line in the program im which the logger is loaded 
 * @param[in] _fileName : file name of the function
 * @param[in] _map : map to be destroyed
 * @param[optional] _moudulName : modul name of the program
 * @param[optional] _message : messate to add to the logger
 */

void GetConfig(ConfigData* _confData, char* _confFileName);

#endif
