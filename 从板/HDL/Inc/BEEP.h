#ifndef BEEP_H
#define BEEP_H

#include "main.h"

/* 蜂鸣器：PA8，高电平响 */
#define BEEP_GPIO_Port  GPIOA
#define BEEP_Pin        GPIO_PIN_8

void beep_init(void);
void beep_on(void);
void beep_off(void);
void beep_alarm(uint8_t times);

#endif
