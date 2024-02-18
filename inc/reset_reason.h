#ifndef TARGET_RESET_REASON_H
#define TARGET_RESET_REASON_H

#include "rebar.h"

/**
 * @brief List of supported reset flags
 * 
 */
typedef enum 
{

    /**
     * @brief Reset caused by software reset
     * 
     */
    TargetResetReasonFlag_SoftwareReset = 0,

    /**
     * @brief Reset caused due to brown out
     * 
     */
    TargetResetReasonFlag_PowerOn,

    /**
     * @brief Reset caused by the watchdog
     * 
     */
    TargetResetReasonFlag_Watchdog,

    /**
     * @brief Reset triggered by the physical reset pin
     * 
     */
    TargetResetReasonFlag_PinReset,

    /**
     * @brief Reset caused by illegal entry into sleep state
     * 
     */
    TargetResetReasonFlag_IllegalSleep,
    
    /**
     * @brief Number of supported reset flags
     * 
     */
    TARGET_RESET_REASON_COUNT

}TargetResetReason;

/**
 * @brief Queries the target to see if a specific reset flag was set
 * 
 * @param Reason Reason to query
 * @param Set Returns true if the reset flag was set
 * @return Error Indication of success or failure
 */
Error TargetResetReason_Query(TargetResetReason Reason, bool *Set);

/**
 * @brief Returns the reset reasom
 * 
 * @param Reason Reason to query
 * @return Error Indication of success or failure
 */
Error TargetResetReason_Get(TargetResetReason *Reason);


/**
 * @brief Clears out reset reason flags
 * 
 * @return Error Indication of success or failure
 */
Error TargetResetReason_ClearFlags();


/**
 * @brief Returns the human readible name of the reset flag
 * 
 * @param Reason reset flag
 * @return const char* 
 */
static inline const char * TargetResetReason_GetName(TargetResetReason Reason)
{
    switch(Reason)
    {
        case TargetResetReasonFlag_PinReset:
            return "Pin Reset";
        case TargetResetReasonFlag_PowerOn:
            return "Power On";
        case TargetResetReasonFlag_SoftwareReset:
            return "Software Reset";
        case TargetResetReasonFlag_Watchdog:
            return "Watchdog";
        case TargetResetReasonFlag_IllegalSleep:
            return "Illegal Sleep";                                
        default:
            return "UNKNOWN";
    }
}


#endif