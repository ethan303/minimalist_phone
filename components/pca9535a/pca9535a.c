#include "driver/i2c_master.h"
#include "include/pca9535a.h"

static i2c_master_bus_handle_t bus_zero_handle;
static i2c_master_dev_handle_t pca_dev_handle;

esp_err_t pca9535a_init(i2c_master_dev_handle_t* dev_handle){
    pca_dev_handle = *dev_handle;
    esp_err_t status;
    ESP_ERROR_CHECK(i2c_master_get_bus_handle(0, &bus_zero_handle));
    if(i2c_master_probe(bus_zero_handle, 0x20, -1) != ESP_OK){ // Let's check that the device is alive.
        ESP_LOGI("PCA9535A INIT", "PCA9535A Device offline, failed to initialize\n");
        return ESP_FAIL;
    } else {
        ESP_LOGI("PCA9535A INIT", "PCA9535A Device online\n");
        return ESP_OK;
    }
    // I2C address 0x20, ESP32S3 I2C controller automatically handles sending start signal and device address
    uint8_t cfg_buf[2] = {CONFIG_PORT1_REG, 0xC4}; // See .h file for details
    write_reg(CONFIG_PORT1_REG, cfg_buf);
    if(read_reg(CONFIG_PORT1_REG) != 0xC4){
        ESP_LOGE("PCA9535A ERROR", "Error setting configuration\n");
    } else {
        ESP_LOGI("PCA9535A INIT", "Configured PCA9535A GPIOs\n");
    }
 
}

esp_err_t pca9535a_set_gpio(uint8_t pin, uint8_t port, bool level){
    // Only for outputs, no impact on GPIOs configured as inputs
    // We should only be using OUT_PORT1_REG here for this device
    uint8_t curr_val = read_reg(OUT_PORT1_REG);
    uint8_t new_val;
    if(level){
        // Set HIGH
        new_val | pin;
    } else {
        // Set LOW
        new_val & ~pin;
    }
    // Send new val
    return write_reg(OUT_PORT1_REG, &new_val);
}

uint8_t read_reg(uint8_t write_reg){
    esp_err_t status;
    uint8_t r_buf;
    status = i2c_master_transmit_receive(pca_dev_handle, &write_reg, 1, &r_buf, 1, -1);
    if(status == ESP_OK){
        return r_buf;
    } else {
        ESP_LOGE("PCA9535A ERROR", "Error reading register\n");
        return 0;
    }
}

esp_err_t write_reg(uint8_t reg, uint8_t* data){
    esp_err_t status;
    uint8_t write_buf[2] = {reg, *data};
    status = i2c_master_transmit(pca_dev_handle, write_buf, sizeof(write_buf), -1);
    if(status != ESP_OK){
        ESP_LOGE("PCA9535A ERROR", "Error writing to register\n");
        return ESP_FAIL;
    } else {
        return ESP_OK;
    }
}