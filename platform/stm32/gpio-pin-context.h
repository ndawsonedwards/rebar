#ifndef _GPIO_PIN_CONTEXT_H_
#define _GPIO_PIN_CONTEXT_H_

#include "stm32l0xx_hal.h"

typedef struct {
    
     int pinEnum;

     GPIO_TypeDef *port;

     uint16_t pin;

}GpioPinContext;

#endif // _GPIO_PIN_CONTEXT_H_