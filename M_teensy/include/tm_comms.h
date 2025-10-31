#ifndef M_ESP32_H_
#define M_ESP32_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TEENSY_I2C_SLAVE_ADDR 0x08

int init_esp32_link();

void esp32_message_check_handle();

void i2c_receive_isr(int n);
void i2c_request_isr();

#ifdef __cplusplus
}
#endif

#endif
