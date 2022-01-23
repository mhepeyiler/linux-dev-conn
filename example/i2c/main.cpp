#include "i2c_dev.h"
#include "logger.h"

int main() {
    I2CDev dev{"/dev/i2c-1"};
    dev.send8(0x23, 0x20, "test", 5);
}