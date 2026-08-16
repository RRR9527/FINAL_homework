#ifndef BREATHING_LED_H
#define BREATHING_LED_H

#include "main.h"   /* HAL_GetTick / __HAL_TIM_SET_COMPARE / uint* 类型 */
#include "tim.h"    /* extern htim3 */

extern volatile uint8_t  is_breathing;
extern volatile uint32_t breath_speed;

void breathing_led(void);

#endif
