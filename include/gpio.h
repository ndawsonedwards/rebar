#ifndef GPIO_PIN_H
#define GPIO_PIN_H

#include "stm32l0xx_hal.h"
#include "errors.h"
#include "gpio-pin-context.h"



/**
 * @brief Initializes the gpio pin for use of accepting predefined enumerations
 * 
 * @param pinContext Pointer to pin context array
 * @param size size of pin context aarray
 * @return Error 
 */
Error Gpio_Initialize(GpioPinContext * pinContext, uint16_t size);


/**
 * @brief Writes teh pin state to the specified pin
 * 
 * @param pin enumerated pin number, as specified in GpioPinContext}
 * @param state pin state, set/clear
 * @return Error 
 */
Error Gpio_Write(uint16_t pin, GPIO_PinState state);

/**
 * @brief reads thh current pin state
 * 
 * @param pin enumerated pin number, as specified in GpioPinContext}
 * @param state pin state, set/clear
 * @return Error 
 */
Error Gpio_Read(uint16_t pin, GPIO_PinState * state);

/**
 * @brief Toggles the pin state of the specified pin
 * 
 * @param pin enumerated pin number, as specified in GpioPinContext}
 * @return Error 
 */
Error Gpio_Toggle(uint16_t pin);



#endif