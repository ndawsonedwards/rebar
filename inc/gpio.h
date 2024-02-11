#ifndef _GPIO_PIN_H_
#define _GPIO_PIN_H_

#include "stm32l0xx_hal.h"
#include "errors.h"



typedef struct {
    
     int pinEnum;

     GPIO_TypeDef *port;

     uint16_t pin;

}GpioPinContext;


/**
 * @brief Initializes the gpio pin for use of accepting predefined enumerations
 * 
 * @param pinContext Pointer to pin context array
 * @param size size of pin context aarray
 * @return Error 
 */
Error Gpio_Initialize(GpioPinContext * pinContext, uint16_t size);



Error Gpio_Write(uint16_t pin, GPIO_PinState state);

Error Gpio_Read(uint16_t pin, GPIO_PinState * state);

Error Gpio_Toggle(uint16_t pin);



#endif