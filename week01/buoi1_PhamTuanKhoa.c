#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
//Task 1 (Pointers & Memory): Bóc tách gói tin cấu hình
void parse_config(const uint8_t *config_packet, int16_t *high_threshold) {
    if (config_packet == NULL||high_threshold == NULL){
        return;
    }
    //config_packet[0]=LSB=00000000 abcdefgh
    //config_packet[1] (dịch trái 8 bit)=MSB=mnefghit 00000000
    *high_threshold=(int16_t)(config_packet[0] | config_packet[1]<<8);
}

//Task 2 (Compiler & Volatile): Đọc thanh ghi cảm biến phần cứng
int16_t read_temperature_reg(void *hw_sensor_reg){
    if (hw_sensor_reg == NULL){
        return 0;
    }
    volatile int16_t *ptr = (volatile int16_t *)hw_sensor_reg;
    return *ptr;
}

//Task 3 (Data Types & Bitwise): Thao tác bit điều khiển thiết bị xuất
void control_output(uint8_t *control_reg,
                    uint8_t fan_enable,
                    uint8_t alarm_enable){
                        if (control_reg==NULL){
                            return;
                        }
                        if (fan_enable == 1){
                            *control_reg |= (1<<0); //Bật bit0 lên 1
                        } else {*control_reg &= ~(1<<0);} //Xóa bit0 về 0
                        if (alarm_enable == 1){
                            *control_reg |= (1<<1); //Bật bit1 lên 1
                        } else {*control_reg &= ~(1<<1);}

                    }
                
int main() {

    // 1. Test Task 1
    int16_t threshold = 0;
    uint8_t mock_packet[2] = {0x64, 0x00};
    parse_config(mock_packet, &threshold); // Có thể thay mock_packet thành NULL để test chống crash khi gặp NULL
    printf("Threshold Parsed: %d C\n", threshold);

    // 2. Test Task 2
    volatile int16_t mock_hardware_sensor = 105; 
    int16_t current_temp = read_temperature_reg((void*)&mock_hardware_sensor);
    printf("Current Temp Read: %d C\n", current_temp);

    // 3. Test Task 3
    uint8_t system_control_register = 0xFC; // 1111 1100
    if (current_temp >= threshold) {
        // Yêu cầu: fan = 1, alarm = 0
        control_output(&system_control_register, 1, 0);
    }
    printf("Control Reg Output: 0x%02X\n", system_control_register);

    return 0;
}