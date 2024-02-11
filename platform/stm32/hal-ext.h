#ifndef _HAL_EXT_H_
#define _HAL_EXT_H_

#include "include.h"
#include "stm32l0xx_hal.h"


/**
 * @brief Converts the HAL_StatusTypeDef status enumeration to Error enumeration 
 * 
 * @param status HAL_StatusTypeDef status to convert into Error type
 * @return Error
 */
static inline Error HalErrors_GetError(HAL_StatusTypeDef status)
{
    switch(status)
    {
        case HAL_OK:
            return Error_None;
        case HAL_ERROR:
            return Error_Unknown;
        case HAL_BUSY:
            return Error_ResourceInUse;
        case HAL_TIMEOUT:
            return Error_Timeout;                                
        default:
            return Error_Unknown;
    }

    return Error_Unknown;
}


#endif // _HAL_EXT_H_
