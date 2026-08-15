#include "LED.h"

const LED_Config_t LED_Config[LED_NUM] = {
    {GPIOA, GPIO_PIN_4},   // LED1
    {GPIOA, GPIO_PIN_5},   // LED2
    {GPIOA, GPIO_PIN_6},   // LED3
    {GPIOA, GPIO_PIN_7},   // LED4
};

void led_on(uint8_t leds) {
    uint8_t i;
    for (i = 0; i < LED_NUM; i++) {
        if (leds & (1U << i)) {
            HAL_GPIO_WritePin(LED_Config[i].port, LED_Config[i].pin, GPIO_PIN_SET);
        }
    }
}

void led_off(uint8_t leds) {
    uint8_t i;
    for (i = 0; i < LED_NUM; i++) {
        if (leds & (1U << i)) {
            HAL_GPIO_WritePin(LED_Config[i].port, LED_Config[i].pin, GPIO_PIN_RESET);
        }
    }
}

void led_toggle(uint8_t leds) {
    uint8_t i;
    for (i = 0; i < LED_NUM; i++) {
        if (leds & (1U << i)) {
            HAL_GPIO_TogglePin(LED_Config[i].port, LED_Config[i].pin);
        }
    }
}
