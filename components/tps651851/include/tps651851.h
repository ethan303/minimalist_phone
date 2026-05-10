#ifndef TPS651861_H
#define TPS651861_H

#include "driver/i2c_master.h"
#include "driver/gpio.h"
void tps651861_init(i2c_master_dev_handle_t*);
void tps651861_power_on();
void tps651861_power_off();

#endif