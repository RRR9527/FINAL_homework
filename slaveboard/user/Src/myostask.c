#include "myostask.h"

volatile uint32_t ledTaskStackHighWaterMark = 0;
volatile uint32_t buzzerTaskStackHighWaterMark = 0;

void Led_Task(void *argument){
    static const uint16_t led_seq[] = {LED_1, LED_2};
    uint8_t i = 0;

    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(250);

    for (;;){
        led_off(LED_1 | LED_2);
        led_on(led_seq[i]);
        i = (i + 1) % 2U;

    ledTaskStackHighWaterMark = uxTaskGetStackHighWaterMark(NULL) * sizeof(StackType_t);
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}