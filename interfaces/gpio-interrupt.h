#ifndef GPIO_INTERRUPT_H
#define GPIO_INTERRUPT_H


#include "rebar.h"


typedef enum
{
    GpioEdgeDetect_Rising,

    GpioEdgeDetect_Falling,

    GpioEdgeDetect_RisingFalling

}GpioEdgeDetect;

typedef struct 
{
    uint16_t pinNumber;

    GpioEdgeDetect edgeDetect;

}GpioInterruptTrigger;


typedef void (*GpioInterruptCallback)(GpioInterruptTrigger trigger);


typedef struct
{
    GpioInterruptTrigger trigger;

    GpioInterruptCallback callback;

}GpioInterruptContext;



/**
 * @brief Register a callback to be called when a desired GPIO interrupts on rising, falling or both edges
 * 
 * @param trigger Trigger info of gpio
 * @param callback Callback to be called 
 * @return AtomosError 
 */
Error GpioInterrupt_RegisterCallback(GpioInterruptTrigger trigger, GpioInterruptCallback callback);

#endif // GPIO_INTERRUPT_H