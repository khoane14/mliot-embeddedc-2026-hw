cmake_minimum_required(VERSION 3.10)

# 1. Định nghĩa hệ thống nhúng trước khi gọi lệnh project
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# 2. Bỏ qua bước kiểm tra C Compiler của CMake
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# 3. Định nghĩa dự án
project(week04 C ASM)


add_compile_definitions(STM32F103xB)

# 4. Các cờ biên dịch vào dự án
add_compile_options(-mcpu=cortex-m3 -mthumb --specs=nosys.specs)


add_link_options(-mcpu=cortex-m3 -mthumb --specs=nosys.specs -T ${CMAKE_SOURCE_DIR}/STM32F103C8Tx_FLASH.ld)

add_executable(${PROJECT_NAME} "")

target_sources(${PROJECT_NAME} PRIVATE
    Task_5.c
    stm32f1xx_hal.c
    stm32f1xx_hal_gpio.c
    stm32f1xx_hal_rcc.c
    stm32f1xx_hal_rcc_ex.c
    stm32f1xx_hal_cortex.c
    stm32f1xx_hal_flash.c
    stm32f1xx_hal_flash_ex.c
    system_stm32f1xx.c
    startup_stm32f103xb.s
)

# Đảm bảo thư mục hiện hành chứa file stm32f1xx_hal_conf.h
target_include_directories(${PROJECT_NAME} PRIVATE .)
# Yêu cầu objcopy tự động tạo file .hex và .bin sau khi build thành công
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.hex
    COMMAND arm-none-eabi-objcopy -O binary $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.bin
)