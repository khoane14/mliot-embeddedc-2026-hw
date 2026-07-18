#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"

void SystemClock_Config(void);

int main(void) {
    HAL_Init(); 
    SystemClock_Config(); 

    __HAL_RCC_GPIOC_CLK_ENABLE(); 

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct); 

    while (1) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        HAL_Delay(500); 
    }
}

void SystemClock_Config(void) {
}

// BỔ SUNG HÀM NÀY ĐỂ HAL_DELAY HOẠT ĐỘNG
void SysTick_Handler(void) {
    HAL_IncTick();
}