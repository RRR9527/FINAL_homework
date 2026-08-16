#include "LED.h"

// void Led_Water(void){
//     LED_ON(1);
//     HAL_Delay(200);
//     LED_OFF(1);
//     HAL_Delay(200);
//     LED_ON(2);
//     HAL_Delay(200);
//     LED_OFF(2);
//     HAL_Delay(200);
//     // LED_ON(3);
//     // HAL_Delay(200);
//     // LED_OFF(3);
//     // HAL_Delay(200);
//     // LED_ON(4);
//     // HAL_Delay(200);
//     // LED_OFF(4);
//     // HAL_Delay(200);
// }

const LED_Config_t LED_Config[] = {
    {LED_2_GPIO_Port, LED_2_Pin},   // 索引2 → LED2
    {LED_1_GPIO_Port, LED_1_Pin},   // 索引1 → LED1
};

void led_on(uint8_t led_id) {
    if (led_id < sizeof(LED_Config) / sizeof(LED_Config[0])) {
        HAL_GPIO_WritePin(LED_Config[led_id].port, LED_Config[led_id].pin, GPIO_PIN_SET);
    }
}

void led_off(uint8_t led_id) {
    if (led_id < sizeof(LED_Config) / sizeof(LED_Config[0])) {
        HAL_GPIO_WritePin(LED_Config[led_id].port, LED_Config[led_id].pin, GPIO_PIN_RESET);
    }
}

void led_toggle(uint8_t led_id) {
    if (led_id < sizeof(LED_Config) / sizeof(LED_Config[0])) {
        HAL_GPIO_TogglePin(LED_Config[led_id].port, LED_Config[led_id].pin);
    }
}
