#ifndef LINUX_DEV_CONN_SRC_I2C_I2C_DEV_H
#define LINUX_DEV_CONN_SRC_I2C_I2C_DEV_H

#include <string_view>
#include <cstdint>
#include <memory>

class I2CDev {
public:
    I2CDev() noexcept;
    I2CDev(std::string_view fileName) noexcept;
    ~I2CDev();
    I2CDev(I2CDev&& other);
    I2CDev(const I2CDev&) = delete;
    I2CDev& operator=(I2CDev&& other);
    I2CDev& operator=(const I2CDev&) = delete;

    bool send8(uint8_t devAddr, uint8_t addr, const void* data, std::size_t size) noexcept;
    bool send16(uint8_t devAddr, uint16_t addr, const void* data, std::size_t size) noexcept;
    std::unique_ptr<uint8_t> read8(uint8_t devAddr, uint8_t addr, std::size_t size) noexcept;
    std::unique_ptr<uint8_t> read16(uint8_t devAddr, uint16_t addr, std::size_t size) noexcept;
    bool read8(uint8_t devAddr, uint8_t addr, uint8_t* dataBuffer, std::size_t size) noexcept;
    bool read16(uint8_t devAddr, uint16_t addr, uint8_t* dataBuffer, std::size_t size) noexcept;

    bool is_initiated() const;
    bool initiate(std::string_view fileName) noexcept;

private:
    bool _init_file() noexcept;
    bool _set_slave_address(uint8_t devAddr) noexcept;
    bool _set_pointer8(uint8_t addr) noexcept;
    bool _set_pointer16(uint16_t addr) noexcept;
    bool _write_data(const void* data, std::size_t size) noexcept;
    bool _read_data(uint8_t* data, std::size_t size) noexcept;
    void _sleep()const noexcept;
    std::string_view _fileName;
    int _fd;
    uint8_t _lastSlaveAddress;
};

#endif