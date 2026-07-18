@echo off

echo STEP 1: CLEANING BUILD FOLDER
if exist build (
    rmdir /s /q build
)

echo.
echo STEP 2: DOING CMAKE CONFIGURATION
cmake -G Ninja -B build

echo.
echo STEP 3: BUILDING PROJECT
ninja -C build

echo.
echo STEP 4: FLASHING AND RESET
STM32_Programmer_CLI -c port=SWD sn=33FF6C064E59313930441243 -w build/stm32f103_aht20_baremetal.bin 0x08000000 -v -rst