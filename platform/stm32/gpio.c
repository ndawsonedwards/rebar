#include "include.h"
#include "stm32l031xx.h"
#include "gpio.h"


static GpioPinContext * _pinContext = NULL;
static uint16_t _size = 0;


static Error  GpioPin_GetPinContext(int pinEnum, GPIO_TypeDef **port, uint16_t *pinNumber) {
    if (ILLEGAL_POINTER(port) || ILLEGAL_POINTER(pinNumber)) {
        return Error_IllegalPointer;
    }

    for (size_t i = 0; i < _size; i++)
    {
        if ( _pinContext[i].pinEnum == pinEnum){

            *port = _pinContext[i].port;
            *pinNumber = _pinContext[i].pin;
            return Error_None;
        }
    }
    
    return Error_NotFound;
}

/**
 * @brief Initializes the gpio pin for use of accepting predefined enumerations. This GPIO module expects that all HAL initialization on supllied pins has already been compeleted
 * 
 * @param pinContext Pointer to pin context array
 * @param size size of pin context aarray
 * @return Error 
 */
Error Gpio_Initialize(GpioPinContext * pinContext, uint16_t size) {

    if (ILLEGAL_POINTER(pinContext)) {
        return Error_IllegalPointer;
    }

    _pinContext = pinContext;
    _size = size;

    return Error_None;
}

Error Gpio_Write(uint16_t pinEnum, GPIO_PinState state) {

    GPIO_TypeDef *port;
    uint16_t pinNumber;

    Error error = GpioPin_GetPinContext(pinEnum, &port, &pinNumber);
    if (error != Error_None ){
        return error;
    }

    HAL_GPIO_WritePin(port,pinNumber,state);

    return Error_None;
}

Error Gpio_Read(uint16_t pin, GPIO_PinState * state) {

    if (ILLEGAL_POINTER(state)) {
        return Error_IllegalPointer;
    }

    GPIO_TypeDef *port;
    uint16_t pinNumber;
    Error error = GpioPin_GetPinContext(pin, &port, &pinNumber);
    if (error != Error_None ){
        return error;
    }

    *state = HAL_GPIO_ReadPin(port, pinNumber);
    return Error_None;

}

Error Gpio_Toggle(uint16_t pin) {

    GPIO_TypeDef *port;
    uint16_t pinNumber;
    Error error = GpioPin_GetPinContext(pin, &port, &pinNumber);
    if (error != Error_None ){
        return error;
    }

    HAL_GPIO_TogglePin(port, pinNumber);
    return Error_None;
}


