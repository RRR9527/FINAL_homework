#include "breathing_led.h"

static uint32_t last_tick = 0U;   /* 上次更新时间，uint32_t 与 HAL_GetTick 对齐 */
static uint8_t  dir       = 1U;   /* 1=增亮 0=变暗 */
static uint16_t level     = 0U;   /* 当前 PWM 占空比 0..999 */

void breathing_led(void)
{
    if (!is_breathing){
        /* 关闭：完全熄灭，并复位状态，下次打开从头开始 */
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
        level = 0U;
        dir = 1U;
        return;
    }

    /* 速度映射：breath_speed 越大越快；1~4ms/步 → 约 2~8s 一个完整呼吸周期（可调） */
    uint32_t interval_time_ms = 1U + ((0xFFFF - breath_speed) >> 12);

    /* 回绕安全的非阻塞判断 */
    if ((HAL_GetTick() - last_tick) >= interval_time_ms){
        last_tick = HAL_GetTick();

        if (dir) {
            level++; 
        } else { 
            level--; 
        }

        /* ARR=999，占空比上限取 999 */
        if (level >= 999){
            dir = 0U; 
        }else if (level == 0){ 
            dir = 1U; 
        }

        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, level);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, level);
    }
}
