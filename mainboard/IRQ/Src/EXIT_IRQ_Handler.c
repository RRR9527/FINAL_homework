#include "EXIT_IRQ_Handler.h"

// volatile uint8_t Beep_Trigger = 0;
extern comprehensive_figures figures;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    /*if (GPIO_Pin == INPUT_Pin){
        if (figures.button.button_state){
            figures.button.button_state = OFF;
            if (time_expire(figures.button.button_timer)){
                figures.signal = BREATHING;
            }else{
                figures.signal = BLINKING;
            }
        }else{
            figures.button.button_state = ON;            
            figures.button.button_timer.time_ticks = 0U;
            figures.the_beep.is_active = ACTIVE;
        }
    }*/
}
