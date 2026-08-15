#include "UART_IRQ_Handler.h"
#include "math.h"
#include <string.h>

uint8_t rx_buffer[5] = {0};
/*
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
   if (huart->Instance == USART1)
   {
        if (rx_buffer[0] == 0xFF)
        {
            // Process the received data
            for (uint8_t i = 1; i < 5; i++)
            {
                if (rx_buffer[i] == 1){
                    // Beep_Trigger ++;  
                }
            }
        }
        HAL_UART_Receive_IT(&huart1, rx_buffer, 5);
   }
}
*/
/*
void UART_Start_Receive(void)
{
    // HAL_UART_ReceiveToIdle_IT(&huart1, rx_buffer, sizeof(rx_buffer));
    HAL_UART_ReceiveToIdle_DMA(&huart1, rx_buffer, 5);
} 

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
    if (huart->Instance == USART1){
        HAL_UART_ReceiveToIdle_IT(&huart1, rx_buffer, sizeof(rx_buffer));
    }
}
*/

void UART_send_sin(float value){
    uint8_t tx_data[8];                                  // 4 字节 float + 4 字节帧尾
    uint8_t frame_tail[4] = {0x00, 0x00, 0x80, 0x7f};    // +Inf，JustFloat 帧尾

    memcpy(tx_data, (uint8_t*)&value, 4);                // 前 4 字节：小端 float
    memcpy(tx_data + 4, frame_tail, 4);                  // 后 4 字节：帧尾

    HAL_UART_Transmit(&huart1, tx_data, sizeof(tx_data), 10);  // 一次发 8 字节
}
