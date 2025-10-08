#ifndef M_ESP32_H_
#define M_ESP32_H_

#define TEENSY_I2C_SLAVE_ADDR 0x08

int init_esp32_link();

void esp32_message_check_handle();

#endif
