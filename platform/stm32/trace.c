#include "trace.h"
#include "stm32l0xx_hal.h"
#include <string.h>
#include <stdio.h>
#include "hal-ext.h"

static UART_HandleTypeDef *_uart;
static TraceLevel _level;



static int Trace_PrependLevel(char *buffer, uint16_t size, TraceLevel level ) {

    char *prepend = "";
    switch (level)
    {
        case TraceLevel_Critical:
            prepend = "[CRIT]";
            break;
        case TraceLevel_Error:
            prepend = "[ERROR]";
            break;    
        case TraceLevel_Warning:
            prepend = "[WARN]";
            break;
        case TraceLevel_Info:
            prepend = "[INFO]";
            break;    
        case TraceLevel_Debug:
            prepend = "[DBG]";
            break;

        default:
            break;
    }
    
    return snprintf(buffer, size, "%s ", prepend); 

}


/**
 * @brief Initialize the trace module for first time use
 * 
 * @param uart uart driver output trace
 * @param level trace logging level
 * @return Error 
 */
Error Trace_Initialize(void *uart, TraceLevel level) {

    if (ILLEGAL_POINTER(uart)) {
        return Error_IllegalPointer;
    }

    _uart = (UART_HandleTypeDef*) uart;
    _level = level;

    return Error_None;
}


static Error Trace_PrintArgs(TraceLevel level, const char *format, va_list args) {

    if (ILLEGAL_POINTER(format)) 
    { 
        return Error_IllegalPointer;
    }

    char buffer[128] = {0};
    int count = Trace_PrependLevel(buffer, sizeof(buffer), level);
    if (count < 0) {
        return Error_RequestFailed;
    }

    (void) vsnprintf(buffer+count, sizeof(buffer)-count, format, args);
    int size = strlen(buffer);
    if (size == 0 ) {
        return Error_OperationCancelled;
    }

    HAL_StatusTypeDef result =  HAL_UART_Transmit(_uart, (uint8_t*) buffer, size, 1000 );
    if (result != HAL_OK) {
        return HalErrors_GetError(result);
    }


    return Error_None;
}

Error Trace_PrintLine(TraceLevel level, const char *format,...) {

    if (ILLEGAL_POINTER(_uart)) 
    { 
        return Error_BadState;
    }

    if (level > _level) {
        return Error_None;
    }


    va_list args;
    va_start(args,format);
    
    Error error = Trace_PrintArgs(level, format, args);
    if (error != Error_None) {
        return error;
    }

    va_end(args);

    char * newLine = "\n";
    HAL_StatusTypeDef result = HAL_UART_Transmit(_uart, (uint8_t*) newLine, strlen(newLine), 1000 );
    if (result != HAL_OK) {
        return HalErrors_GetError(result);
    }

    return Error_None;
}



Error Trace_Print(TraceLevel level, const char *format,...)
{
    if (ILLEGAL_POINTER(_uart)) 
    { 
        return Error_BadState;
    }

    if (level > _level) {
        return Error_None;
    }

    va_list args;
    va_start(args,format);

    Error error = Trace_PrintArgs(level, format, args);
    if (error != Error_None) {
        return error;
    }
    
    va_end(args);

    return Error_None;
}

void Trace_SetLevel(TraceLevel level) {
    _level = level;
}
