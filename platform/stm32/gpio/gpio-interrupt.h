#ifndef GPIO_INTERRUPT_H
#define GPIO_INTERRUPT_H


#include "rebar.h"

/**
 * @brief enumerations of Gpio edge detection
 * 
 */
typedef enum
{
    /**
     * @brief Edge detection for rising edge
     * 
     */
    GpioEdgeDetect_Rising,
    /**
     * @brief Edge detection for falling edge
     * 
     */
    GpioEdgeDetect_Falling,
    /**
     * @brief Edge detection for both rising and falling edge
     * 
     */
    GpioEdgeDetect_RisingFalling

}GpioEdgeDetect;


typedef struct 
{
    uint16_t pinNumber;

    GpioEdgeDetect edgeDetect;

}GpioInterruptTrigger;


typedef void (*GpioInterruptCallback)(GpioInterruptTrigger trigger);

/**
 * @brief Gpio Interrupt context for handling interrupt events. Callback will be triggered with 
 *      trigger metrics match interrupt event
 */
typedef struct
{
    GpioInterruptTrigger trigger;

    GpioInterruptCallback callback;

}GpioInterruptContext;

/**
 * @brief Provides memory allocation for GpioInterrupt module. Context param can be NULL if associated length is 0
 * 
 * @param risingContext rising contxt
 * @param risingCapacity total capacity of context. The number of unique rising interrupt events
 * @param fallingContext falling contexts
 * @param fallingCapacity total capacity of context. The number of unique rising interrupt events
 * @return Error 
 */
Error GpioInterrupt_Initialize(GpioInterruptContext *risingContext, uint8_t risingCapacity, GpioInterruptContext *fallingContext, uint8_t fallingCapacity);

/**
 * @brief Register a callback to be called when a desired GPIO interrupts on rising, falling or both edges
 * 
 * @param context Interrupt information for trigger and response
 * @return AtomosError 
 */
Error GpioInterrupt_RegisterCallback(GpioInterruptContext *context);

#endif // GPIO_INTERRUPT_H