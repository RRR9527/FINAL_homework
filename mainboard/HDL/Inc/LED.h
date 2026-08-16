#ifndef LED_H
#define LED_H

#include "main.h"
#include "gpio.h"

#define LED_ON(x) HAL_GPIO_WritePin(LED_##x##_GPIO_Port, LED_##x##_Pin, GPIO_PIN_SET)
#define LED_OFF(x) HAL_GPIO_WritePin(LED_##x##_GPIO_Port, LED_##x##_Pin, GPIO_PIN_RESET)
#define LED_TOGGLE(x) HAL_GPIO_TogglePin(LED_##x##_GPIO_Port, LED_##x##_pin) 

typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
} LED_Config_t;

// 用已有的宏组装出数组
extern const LED_Config_t LED_Config[];

// void Led_Water(void);
void led_on(uint8_t led_id);
void led_off(uint8_t led_id);
void led_toggle(uint8_t led_id);

#endif