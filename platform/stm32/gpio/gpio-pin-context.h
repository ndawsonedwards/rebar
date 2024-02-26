#ifndef GPIO_PIN_CONTEXT_H
#define GPIO_PIN_CONTEXT_H

#include "stm32l0xx_hal.h"

typedef struct {
    
     int pinEnum;

     GPIO_TypeDef *port;

     uint16_t pin;

}GpioPinContext;

#endif // GPIO_PIN_CONTEXT_H