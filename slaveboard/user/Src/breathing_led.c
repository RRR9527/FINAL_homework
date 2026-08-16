#include "breathing_led.h"
#include "can.h"

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

    CAN_TxHeaderTypeDef TxHeader;
    uint32_t TxMailbox;  // 用于记录这次发送用了哪个邮箱
    uint8_t TxData[5] = {
        is_breathing, 
        (uint8_t)(breath_speed >> 8), 
        (uint8_t)(breath_speed & 0xFF),        
        (uint8_t)(level >> 8), 
        (uint8_t)(level & 0xFF)
    };  // 要发送的数据

    TxHeader.StdId = 0x202;  // 输入11位标准ID
    TxHeader.ExtId = 0;
    TxHeader.IDE = CAN_ID_STD;  // 标准帧
    TxHeader.RTR = CAN_RTR_DATA;  // 数据帧
    TxHeader.DLC = 5;  // 数据长度（0 - 8）
    TxHeader.TransmitGlobalTime = DISABLE;  // 禁用时间戳

    // 向主人发送命令
    HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
}
