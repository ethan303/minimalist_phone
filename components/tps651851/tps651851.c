#include "include/tps651851.h"

void tps651851_init(i2c_master_dev_handle_t* tps_handle){
    // Initialize PMIC for high voltage rails for driving E-ink display
    // PRECONDITION: tps651851 is initialized as device on i2c bus with addr 0x68

    // 1.) Wakeup device by pulling WAKEUP pin high
    
}