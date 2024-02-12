#ifndef _SYSTEM_TIME_H_
#define _SYSTEM_TIME_H_

#include "include.h"

typedef uint32_t TimeStamp;

/**
 * @brief Gets the amount ms that have elapsed since boot
 * 
 * @param timeStamp Current timestamp in milliseconds since boot
 * @return Error 
 */
Error SystemTime_GetTimeStampMs(TimeStamp *timeStamp);

/**
 * @brief Returns the amount of time in millisencs that have elapsed since 
 * 
 * @param start starting timestampe to get the time since
 * @param elapsed total that that has elapsed since
 * @return Error 
 */
Error SystemTime_GetMillisecondsSince(TimeStamp start, TimeStamp *elapsed);

#endif // _SYSTEM_TIME_H_