#ifndef MYOSTASK_H
#define MYOSTASK_H


#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "LED.h"
#include "BEEP.h"

void Led_Task(void *argument);
void Beep_Task(void *argument);

#endif