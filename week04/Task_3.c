#include "main.h"

int main(void) {
    // Khởi tạo thư viện HAL và hệ thống thời gian cơ bản
    HAL_Init(); 

    // Bật xung nhịp cho cổng GPIOC
    __HAL_RCC_GPIOC_CLK_ENABLE(); 

    // Cấu hình chân PC13 làm ngõ ra (Output) để điều khiển LED
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct); 

    // Vòng lặp vô hạn nhấp nháy LED
    while (1) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        HAL_Delay(500); // Trì hoãn 500ms
    }
}