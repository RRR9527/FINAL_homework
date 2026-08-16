#include "BEEP.h"

void beep_on(void) {
    HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET);
}

void beep_off(void) {
    HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);
}

void beep_init(void) {
    beep_on();
    HAL_Delay(200);
    beep_off();
    HAL_Delay(200);
    beep_on();
    HAL_Delay(50);
    beep_off();
    HAL_Delay(50);
    beep_on();
    HAL_Delay(50);
    beep_off();
    HAL_Delay(50);
}

void beep_alarm(uint8_t times) {
    uint8_t i;
    for (i = 0; i < times; i++) {
        beep_on();
        HAL_Delay(40);
        beep_off();
        HAL_Delay(40);
    }
}
