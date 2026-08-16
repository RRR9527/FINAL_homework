#include "CAN_IRQ_Handler.h"
#include "usart.h"      // extern UART_HandleTypeDef huart1
#include <string.h>     // memcpy

CAN_RxHeaderTypeDef RxHeader;
uint8_t RxData[8];
volatile uint8_t Beep_Trigger;
volatile uint8_t  slave_is_breathing;
volatile uint32_t slave_breath_speed;
volatile uint32_t slave_level;
volatile uint8_t  telemetry_ready = 0U;   // 新数据标志：ISR 置位，任务清位

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){
    if (hcan->Instance == CAN1){
        if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK){
            if (RxHeader.StdId == 0x202){
                slave_is_breathing = RxData[0];
                slave_breath_speed = (RxData[1] << 8) | (RxData[2]);
                slave_level        = (RxData[3] << 8) | (RxData[4]);
                telemetry_ready    = 1U;    // 只置标志，不在中断里发送
            }
        }
    }
}

/* 任务上下文调用：标志置位时打包 3 路 float + JustFloat 帧尾发送 */
void CAN_Telemetry_Send(void){
    if (telemetry_ready == 0U) return;

    float   f[3] = {(float)slave_is_breathing,
                    (float)slave_breath_speed,
                    (float)slave_level};

    uint8_t tx_data[16];
    
    memcpy(&tx_data[0], &f[0], 4);
    memcpy(&tx_data[4], &f[1], 4);
    memcpy(&tx_data[8], &f[2], 4);
    tx_data[12] = 0x00;   // JustFloat 帧尾 +Inf
    tx_data[13] = 0x00;
    tx_data[14] = 0x80;
    tx_data[15] = 0x7F;

    HAL_UART_Transmit(&huart1, tx_data, sizeof(tx_data), 10);
    telemetry_ready = 0U;
}
