#include "CAN_IRQ_Handler.h"

CAN_RxHeaderTypeDef RxHeader;
uint8_t RxData[8];
// volatile uint8_t Beep_Trigger;
volatile uint8_t is_breathing;
volatile uint32_t breath_speed;

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){
    // 接收主人的命令
    if (hcan->Instance == CAN1){
        if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK){
            if (RxHeader.StdId == 0x201){
                is_breathing = RxData[0];
                breath_speed = (RxData[1] << 8) | RxData[2];
                
            }
        }
    } 
}