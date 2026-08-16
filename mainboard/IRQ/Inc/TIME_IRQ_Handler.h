#ifndef TIME_IRQ_HANDLER_H
#define TIME_IRQ_HANDLER_H

#include "main.h"
#include "tim.h"
#include "EXIT_IRQ_Handler.h"
#include "LED.h"
// extern TIM_HandleTypeDef htim2; 

#define time_expire(timer_ptr) ((timer_ptr).time_ticks >= (timer_ptr).duration)

volatile typedef struct{
    // uint32_t begin_time;
    uint16_t duration;
    uint16_t time_ticks;
} Timer;

volatile typedef struct{
    uint8_t button_state;
    Timer   button_timer;
} buttons;

volatile typedef struct{
    uint8_t  current_led;
    uint8_t  led_state;
    uint8_t  breath_direction;
    uint16_t level;
    Timer    led_timer;
} all_leds;

volatile typedef struct{
    uint8_t beep_state;
    uint8_t is_active;
    Timer   beep_timer;
} beep_figure;

volatile typedef struct {
    buttons     button;
    all_leds    leds;
    uint8_t     signal;
    beep_figure the_beep;
} comprehensive_figures;

#define IDLE 0U
#define BLINKING 1U
#define BREATHING 2U
#define BUTTON_ON 1U
#define BUTTON_OFF 0U
#define LED_1 0U
#define LED_2 1U
#define ON 1U
#define OFF 0U
#define ACTIVE 1U
#define INACTIVE 0U

void TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif