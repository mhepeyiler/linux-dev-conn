#ifndef LINUX_DEV_CONN_SRC_INCLUDE_COMM_DEVICE_H
#define LINUX_DEV_CONN_SRC_INCLUDE_COMM_DEVICE_H

#include <memory>

class CommDevice {
public:
    virtual void send(uint16_t devAddress, uint16_t address, const char* data, std::size_t dataSize) noexcept = 0;
    virtual void read(uint16_t devAddress, uint16_t address, std::size_t dataSize, char* data) noexcept = 0;
    virtual std::unique_ptr<char> read(uint16_t devAddress, uint16_t address, std::size_t dataSize) noexcept = 0;
};

#endif