#ifndef CAN_IRQHANDLER_H
#define CAN_IRQHANDLER_H

#include "main.h"
#include "can.h"
#include "EXIT_IRQ_Handler.h"

extern volatile uint8_t  slave_is_breathing;
extern volatile uint32_t slave_breath_speed;
extern volatile uint32_t slave_level;
extern volatile uint8_t  telemetry_ready;

void CAN_Telemetry_Send(void);

#endif
