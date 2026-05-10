#include "esp_log.h"
#include "../lib/pins.h"
#include "driver/i2c_master.h"
#include "freertos/FreeRTOS.h"
#include "../components/tps651851/include/tps651851.h"
#include "../components/pca9535a/include/pca9535a.h"

// I2C definitions
i2c_master_bus_handle_t i2c_bus_handle;
i2c_master_dev_handle_t dev_handle_tps651861;
i2c_master_dev_handle_t dev_handle_pca9535a;

SemaphoreHandle_t i2c_lock; // For now we only use one i2c bus 

void i2c_init();

void app_main() {
    i2c_init(); // Initialize all i2c device 
    
    

}

void i2c_init(){
    i2c_master_bus_config_t i2c_master_cfg = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_NUM_0,
        .scl_io_num = SCL,
        .sda_io_num = SDA,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true
    };
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_master_cfg, &i2c_bus_handle));
    // Initialize all devices (add as we go)
    i2c_device_config_t dev_tps651851_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = 0x68,
        .scl_speed_hz = 100000
    };
    i2c_device_config_t dev_pca9535a_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = 0x20,
        .scl_speed_hz = 100000
    };
    
    ESP_ERROR_CHECK(i2c_master_bus_add_device(i2c_bus_handle, &dev_tps651851_cfg, &dev_handle_tps651861));
    ESP_ERROR_CHECK(i2c_master_bus_add_device(i2c_bus_handle, &dev_pca9535a_cfg, &dev_handle_pca9535a));

    
}