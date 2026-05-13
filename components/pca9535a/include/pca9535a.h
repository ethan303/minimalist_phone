#ifndef PCA9535A_H
#define PCA9535A_H

#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "esp_log.h"

// Register map
#define IN_PORT0_REG 0x00
#define IN_PORT1_REG 0x01
#define OUT_PORT0_REG 0x02
#define OUT_PORT1_REG 0x03
#define POL_INV_PORT0_REG 0x04
#define POL_INV_PORT1_REG 0x05
#define CONFIG_PORT0_REG 0x06
#define CONFIG_PORT1_REG 0x07


// PCA9535A Expansion Pinout:
    /*
        IO1_0 -> EP_OE          (OUT) -> E-Paper Output enable source driver
        IO1_1 -> EP_MODE        (OUT) -> E-Paper Output mode selection gate driver
        IO1_2 -> BUTTON         (IN)
        IO1_3 -> TPS_PWRUP      (OUT)
        IO1_4 -> VCOM_CTRL      (OUT)
        IO1_5 -> TPS_WAKEUP     (OUT)
        IO1_6 -> TPS_PWR_GOOD   (IN)
        IO1_7 -> TPS_INT        (IN)
        So, register config: (1 = input, 0 = output)
        CONFIG_PORT1_REG (0x06) => 0b1100_0100 (0xC4)
    */

esp_err_t pca9535a_init(i2c_master_dev_handle_t* handle);
esp_err_t pca9535a_set_gpio_port1(uint8_t pin, uint8_t port, bool level);

uint8_t read_reg(uint8_t reg);
esp_err_t write_reg(uint8_t reg, uint8_t* data);

#endif