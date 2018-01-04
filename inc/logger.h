#ifndef __LOGGER__
#define __LOGGER__

/** 
 *  @file logger.h
 *  @brief basic functions to create a logger that load basic info of each function in a program to a file. the logger will close itself once the program will end.
	 *  
 *  @author Ido Naveh idonovo@gmail.com
 */

#include <stdio.h>   
#include "config.h"

typedef struct LogData LogData;

typedef enum
{
    LOG_TRACE    =0,
    LOG_DEBUG,
   	LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_CRITICAL,
    LOG_SEVRE,
    LOG_FATAL,
    LOG_NONE
} LogLevels;


/** 
 * 
 * @brief a function to send a log to a function.
 * @param[in] _configFileName : configuration FileName.
 * @returns  ADT which hold logger info or NULL if errror occure
 */

LogData* GetLog(char* _configFileName);

/** 
 * 
 * @brief a function to write oon file using a logger basic info of a function in a program.
 * @param[in] _logData : ADT to hold logger info.
 * @param[in] _logLevel : the enum numeric value
 * @param[in] _funcName : function name
 * @param[in] _line, : line in the program im which the logger is loaded 
 * @param[in] _fileName : file name of the function
 * @param[in] _map : map to be destroyed
 * @param[optional] _moudulName : modul name of the program
 * @param[optional] _message : messate to add to the logger

 */
 
void LogWrite(LogData* _logData, int _logLevel, const char* _funcName, int _line, const char* _fileName, const char* _message);



#endif
