#include "UART_IRQ_Handler.h"
#include "can.h"
#include "CAN_IRQ_Handler.h"

uint8_t rx_buffer[100] = {0};  // 接收到的信息
// uint8_t tx_buffer[100] = {0};  // 发送出去的信息
volatile uint8_t is_breathing = 0U;
volatile uint32_t breath_speed = 0U;

void UART_Start_Receive(void)
{
    // HAL_UART_ReceiveToIdle_IT(&huart1, rx_buffer, sizeof(rx_buffer));
    HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buffer, sizeof(rx_buffer));
} 

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){   // 空闲中断。这个size是自动获取并传入的，所以可以不定长度
    if (huart->Instance == USART1){
        if ((rx_buffer[0] == 0xA5) && rx_buffer[4] == 0x5A && (Size == 5))
        {
            // Process the received data
            uint8_t frame_ok = 0U;

            if (rx_buffer[1] == 0x00){
                is_breathing = 0U;
                frame_ok = 1U;
            }else if (rx_buffer[1] == 0x01){
                is_breathing = 1U;
                frame_ok = 1U;
            }

            if (frame_ok){
                breath_speed = (rx_buffer[2] << 8) | rx_buffer[3];
            }

            CAN_TxHeaderTypeDef TxHeader;
            uint32_t TxMailbox;  // 用于记录这次发送用了哪个邮箱
            uint8_t TxData[3] = {rx_buffer[0], rx_buffer[1], rx_buffer[2]};  // 要发送的数据

            TxHeader.StdId = 0x201;  // 输入11位标准ID
            TxHeader.ExtId = 0;
            TxHeader.IDE = CAN_ID_STD;  // 标准帧
            TxHeader.RTR = CAN_RTR_DATA;  // 数据帧
            TxHeader.DLC = 3;  // 数据长度（0 - 8）
            TxHeader.TransmitGlobalTime = DISABLE;  // 禁用时间戳

            HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
        }
        HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buffer, sizeof(rx_buffer));  // 重启接收（空闲中断）
    }
}
