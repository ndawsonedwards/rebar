#include "system_time.h"
#include "stm32l0xx_hal.h"
#include "trace.h"



/**
 * @brief Gets the amount ms that have elapsed since boot
 * 
 * @param timeStamp Current Timestamp 
 * @return Error 
 */
Error SystemTime_GetTimeStampMs(TimeStamp *timeStamp)
{

    uint32_t tick = HAL_GetTick();
    HAL_TickFreqTypeDef freq = HAL_GetTickFreq();

    switch (freq) {

        case HAL_TICK_FREQ_1KHZ:
            *timeStamp = tick;
            break;
        case HAL_TICK_FREQ_10HZ:
            *timeStamp = tick / 10;
            break;
        case HAL_TICK_FREQ_100HZ:
            *timeStamp = tick / 100;
            break;

        default:
            return Error_Unknown;
   
    }

    return Error_None;
}

/**
 * @brief Returns the amount of time in millisencs that have elapsed since 
 * 
 * @param start starting timestampe to get the time since
 * @param elapsed total that that has elapsed since
 * @return Error 
 */
Error SystemTime_GetMillisecondsSince(TimeStamp start, TimeStamp *elapsed) {

    if (ILLEGAL_POINTER(elapsed)) {
        return Error_IllegalPointer;
    }

    
    TimeStamp tick = HAL_GetTick();
    HAL_TickFreqTypeDef freq = HAL_GetTickFreq();

    //handle overflow
    uint32_t delta = (tick >= start) ? (tick - start) : (0xFFFFFFFFU - start) + tick;

     switch (freq) {
        case HAL_TICK_FREQ_1KHZ:
            *elapsed = delta;
            break;
        case HAL_TICK_FREQ_10HZ:
            *elapsed = delta / 10;
            break;
        case HAL_TICK_FREQ_100HZ:
            *elapsed = delta / 100;
            break;

        default:
            return Error_Unknown;
   
    }


    return Error_None;
}