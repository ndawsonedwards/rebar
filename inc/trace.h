#ifndef _TRACE_H_
#define _TRACE_H_

#include "include.h"

typedef enum  {

    /**
     * @brief Disables all trace activity
     */
    TraceLevel_Off = 0,

    /**
     * @brief Contains critical error information, such as hardware failures
     */    
    TraceLevel_Critical,

    /**
     * @brief Contain error information regarding a failed operation
     */    
    TraceLevel_Error,

    /**
     * @brief Contains error invormation that an event occured that is not recommended. Less severe than an Error, but may lead to unexpected behavior
     */    
    TraceLevel_Warning,

    /**
     * @brief Contains informaiton about successful operations in teh application
     */
    TraceLevel_Info,

    /**
     * @brief Contains information that is only useful for debugging
     */    
    TraceLevel_Debug

}TraceLevel;


/**
 * @brief Initialize the trace module for first time use
 * 
 * @param uart uart driver output trace
 * @param level trace logging level
 * @return Error 
 */
Error Trace_Initialize(void * uart, TraceLevel level);

/**
 * @brief Sends message to the trace
 * 
 * @param Format Formatted message
 * @param ...  args
 * @return Error 
 */
Error Trace_Print(TraceLevel level, const char *Format,...);

/**
 * @brief Sends message appended with newline to the trace
 * 
 * @param Format Formatted message
 * @param ...  args
 * @return Error 
 */
Error Trace_PrintLine(TraceLevel level, const char *Format,...);

/**
 * @brief Sets trace level
 * 
 */
void Trace_SetLevel(TraceLevel level);
 
 
#define PRINT_DEBUG(Format)     Trace_Print(TraceLevel_Debug, Format, ...)
#define PRINT_INFO(Format)      Trace_Print(TraceLevel_Info, Format, ...)
#define PRINT_WARN(Format)      Trace_Print(TraceLevel_Warning, Format, ...)
#define PRINT_ERROR(Format)     Trace_Print(TraceLevel_Error, Format, ...)
#define PRINT_CRITICAL(Format)  Trace_Print(TraceLevel_Critical, Format, ...)


#endif //_TRACE_H_