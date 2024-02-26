#include "gpio-interrupt.h"


#define MAX_RISING_SIZE 3
#define MAX_FALLING_SIZE 3

uint8_t _risingLength = 0;
uint8_t _fallingLength = 0;

GpioInterruptContext _risingContext[MAX_RISING_SIZE];
GpioInterruptContext _fallingContext[MAX_FALLING_SIZE];


void HAL_GPIO_EXTI_Rising_Callback(uint16_t gpioPin)
{
    uint8_t i;
    for (i = 0; i < _risingLength; i++)
    {
        if (_risingContext[i].trigger.pinNumber != gpioPin)
        {
            continue;
        }

        if ( ILLEGAL_POINTER( _risingContext[i].callback ))
        {
            return;
        }

        GpioInterruptTrigger trigger = { .pinNumber = gpioPin, .edgeDetect = GpioEdgeDetect_Rising};
        _risingContext[i].callback(trigger);
    }
}

void HAL_GPIO_EXTI_Falling_Callback(uint16_t gpioPin)
{
    uint8_t i;
    for (i = 0; i < _fallingLength; i++)
    {
        if (_fallingContext[i].trigger.pinNumber != gpioPin)
        {
            continue;
        }

        if ( ILLEGAL_POINTER( _fallingContext[i].callback ))
        {
            return;
        }

        GpioInterruptTrigger trigger = { .pinNumber = gpioPin, .edgeDetect = GpioEdgeDetect_Falling};
        _fallingContext[i].callback(trigger);
    }	
}


/**
 * @brief Register a callback to be called when a desired GPIO interrupts on rising, falling or both edges
 * 
 * @param trigger GPIO pin state to trigger on
 * @param Callback Callback to be called 
 * @return Error 
 */
Error GpioInterrupt_RegisterCallback(GpioInterruptTrigger trigger, GpioInterruptCallback Callback)
{
    if (ILLEGAL_POINTER(Callback))
    {
        return Error_BadParameter;
    }
    if (_risingLength >= MAX_RISING_SIZE)
    {
        return Error_InsufficientMemory;
    }

    if ((trigger.edgeDetect == GpioEdgeDetect_Rising) || (trigger.edgeDetect == GpioEdgeDetect_RisingFalling) )
    {
        if (_risingLength >= MAX_FALLING_SIZE)
        {
            return Error_InsufficientMemory;
        }
        _risingContext[_risingLength].trigger = trigger;
        _risingContext[_risingLength].callback = Callback;
        _risingLength++;
    }


    if ((trigger.edgeDetect == GpioEdgeDetect_Falling) || (trigger.edgeDetect == GpioEdgeDetect_RisingFalling))
    {
        if (_fallingLength >= MAX_FALLING_SIZE)
        {
            return Error_InsufficientMemory;
        }
        _fallingContext[_fallingLength].trigger = trigger;
        _fallingContext[_fallingLength].callback = Callback;
        _fallingLength++;
    }

    return Error_None;
}
