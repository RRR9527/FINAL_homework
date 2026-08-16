#include "UART_IRQ_Handler.h"
#include "math.h"
#include <string.h>

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
        }
        HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buffer, sizeof(rx_buffer));  // 重启接收（空闲中断）
    }
}
