#include <string.h>
#include "gpio-interrupt.h"
#include "linked-list.h"


typedef struct {
    GpioInterruptContext * context;
    uint8_t length;
    uint8_t capacity;
}GpioInterruptArray;


static GpioInterruptArray _risingArray = {0};
static GpioInterruptArray _fallingArray = {0};

void HAL_GPIO_EXTI_Rising_Callback(uint16_t gpioPin)
{
    for (uint8_t i = 0; i < _risingArray.length; i++) {
        if (_risingArray.context[i].trigger.pinNumber != gpioPin) {
            continue;
        }

        if ( ILLEGAL_POINTER( _risingArray.context[i].callback )) {
            return;
        }

        GpioInterruptTrigger trigger = { .pinNumber = gpioPin, .edgeDetect = GpioEdgeDetect_Rising};
        _risingArray.context[i].callback(trigger);
    }
}

void HAL_GPIO_EXTI_Falling_Callback(uint16_t gpioPin)
{
    for (uint8_t i = 0; i < _fallingArray.length; i++) {
        if (_fallingArray.context[i].trigger.pinNumber != gpioPin) {
            continue;
        }

        if ( ILLEGAL_POINTER( _fallingArray.context[i].callback )) {
            return;
        }

        GpioInterruptTrigger trigger = { .pinNumber = gpioPin, .edgeDetect = GpioEdgeDetect_Falling};
        _fallingArray.context[i].callback(trigger);
    }	
}

/**
 * @brief Provides memory allocation for GpioInterrupt module. Context param can be NULL if associated length is 0
 * 
 * @param risingContext rising contxt
 * @param risingCapacity total capacity of context. The number of unique rising interrupt events
 * @param fallingContext falling contexts
 * @param fallingCapacity total capacity of context. The number of unique rising interrupt events
 * @return Error 
 */
Error GpioInterrupt_Initialize(GpioInterruptContext *risingContext, uint8_t risingCapacity, GpioInterruptContext *fallingContext, uint8_t fallingCapacity) {

    if (risingCapacity > 0)
    {
        if ( ILLEGAL_POINTER(risingContext) ) {
            return Error_IllegalPointer;
        }

        _risingArray.context = risingContext;
        _risingArray.capacity = risingCapacity;
        _risingArray.length = 0;
    }

    if (fallingCapacity > 0)
    {
        if ( ILLEGAL_POINTER(risingContext) ) {
            return Error_IllegalPointer;
        }
        _fallingArray.context = fallingContext;
        _fallingArray.capacity = fallingCapacity;
        _fallingArray.length = 0;
    }

    return Error_None;
}



/**
 * @brief Register a callback to be called when a desired GPIO interrupts on rising, falling or both edges
 * 
 * @param trigger GPIO pin state to trigger on
 * @param Callback Callback to be called 
 * @return Error 
 */
Error GpioInterrupt_RegisterCallback(GpioInterruptContext *context)
{
    if (ILLEGAL_POINTER(context)) {
        return Error_IllegalPointer;
    }

    if (ILLEGAL_POINTER(context->callback)) {
        return Error_IllegalPointer;
    }


    if ((context->trigger.edgeDetect == GpioEdgeDetect_Rising) || (context->trigger.edgeDetect == GpioEdgeDetect_RisingFalling) )
    {
        if (_risingArray.length >= _risingArray.capacity)
        {
            return Error_InsufficientMemory;
        }

        memcpy(&_risingArray.context[_risingArray.length], context, sizeof(GpioInterruptContext));
        _risingArray.length++;
    }


    if ((context->trigger.edgeDetect == GpioEdgeDetect_Falling) || (context->trigger.edgeDetect == GpioEdgeDetect_RisingFalling))
    {
        if (_fallingArray.length >= _fallingArray.capacity)
        {
            return Error_InsufficientMemory;
        }

        memcpy(&_fallingArray.context[_fallingArray.length], context, sizeof(GpioInterruptContext));
        _fallingArray.length++;
    }

    return Error_None;
}
