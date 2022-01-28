#include "i2c_dev.h"
#include "logger.h"

int main() {
    I2CDev dev{"/dev/i2c-0"};
    dev.send8(0x23, 0x20, "test\n", 6);
    auto res = dev.read8(0x23, 0x20, 5);
    if (res == nullptr) {
        LOG_FATAL("Read failed");
    } else {
        LOG_INFO("Received message %s", *res);
    }
}