#include "TIME_IRQ_Handler.h"

uint16_t tim1_counter = 0;
static uint8_t dir = 1;

comprehensive_figures figures = {
    .button = {
        .button_state = BUTTON_OFF, 
        .button_timer = {.time_ticks = 0U, .duration = 1000U}
    },
    .leds = {
        .current_led = LED_1, 
        .led_state = OFF, 
        .breath_direction = 1, 
        .level = 0U, 
        .led_timer = {.time_ticks = 0U, .duration = 100U}
    },
    .signal = IDLE,
    .the_beep = {
        .beep_state = OFF, 
        .is_active = INACTIVE, 
        .beep_timer = {.time_ticks = 0U, .duration = 50U}
    }
};

void TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        if (figures.the_beep.is_active){
            if (time_expire(figures.the_beep.beep_timer)){
                if (figures.the_beep.beep_state){
                    BEEP_OFF();
                    figures.the_beep.beep_state = OFF;
                    figures.the_beep.beep_timer.time_ticks = 0U;
                    figures.the_beep.is_active = INACTIVE;
                }else {
                    BEEP_ON();
                    figures.the_beep.beep_state = ON;
                    figures.the_beep.beep_timer.time_ticks = 0U;
                }
            }
            figures.the_beep.beep_timer.time_ticks += 2U;
        }else{
            figures.the_beep.beep_timer.time_ticks = 0U;
        }

        if (figures.button.button_state){
            figures.button.button_timer.time_ticks += 2U;
        }

        switch (figures.signal){

            case IDLE:{
                led_off(LED_1);
                led_off(LED_2);
                break;
            }


            case BLINKING:{
                if (time_expire(figures.leds.led_timer)){
                    if (figures.leds.led_state){
                        led_off(figures.leds.current_led);
                        figures.leds.led_state = OFF;
                        figures.leds.current_led = (figures.leds.current_led + 1) % 2U;
                        figures.leds.led_timer.time_ticks = 0U;
                    }else{
                        led_on(figures.leds.current_led);
                        figures.leds.led_state = ON;
                        figures.leds.led_timer.time_ticks = 0U;
                    }                    
                }

                break;
            }

            case BREATHING:{
                if (figures.leds.breath_direction){
                    figures.leds.level ++;
                }else{
                    figures.leds.level --;
                }

                if (figures.leds.level >= 1000U){
                    figures.leds.breath_direction = 0;
                }else if (figures.leds.level == 0){
                    figures.leds.breath_direction = 1;
                }

                __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, figures.leds.level);
                __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, figures.leds.level);
                break;
            }
        }

        if (figures.signal){
            figures.leds.led_timer.time_ticks += 2;
        }        
    }
}
