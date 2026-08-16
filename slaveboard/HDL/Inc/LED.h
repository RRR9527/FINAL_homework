#ifndef LED_H
#define LED_H

#include "main.h"

/* LED 引脚映射：LED1~LED4 对应 PA4~PA7（高电平点亮） */
#define LED_NUM  4

/* LED 位掩码：LED_1~LED_4，编号从 1 开始 */
#define LED_1    (1U << 0)
#define LED_2    (1U << 1)
#define LED_3    (1U << 2)
#define LED_4    (1U << 3)
#define LED_ALL  (LED_1 | LED_2 | LED_3 | LED_4)

typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
} LED_Config_t;

extern const LED_Config_t LED_Config[LED_NUM];

/* leds 为位掩码，可组合：led_on(LED_1 | LED_2) */
void led_on(uint8_t leds);
void led_off(uint8_t leds);
void led_toggle(uint8_t leds);

#endif
