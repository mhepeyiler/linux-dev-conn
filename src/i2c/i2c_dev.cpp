#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>

#include "i2c_dev.h"
#include "logger.h"

I2CDev::I2CDev() noexcept : _fileName{},
                            _fd{-1},
                            _lastSlaveAddress{0} {
}

I2CDev::I2CDev(std::string_view fileName) noexcept : _fileName{fileName},
                                                     _fd{-1},
                                                     _lastSlaveAddress{0} {
    this->initiate(fileName);
}

I2CDev::~I2CDev() {
    close(_fd);
}

I2CDev::I2CDev(I2CDev &&other) : _fileName{other._fileName},
                                 _fd{other._fd},
                                 _lastSlaveAddress{other._lastSlaveAddress} {
    other._fd = -1;
}

I2CDev &I2CDev::operator=(I2CDev &&other) {
    _fileName = other._fileName;
    _fd = other._fd;
    _lastSlaveAddress = other._lastSlaveAddress;
    other._fd = -1;
}

bool I2CDev::send8(uint8_t devAddr, uint8_t addr, const void *data, std::size_t size) noexcept {
    if (!_set_slave_address(devAddr) && !_set_pointer8(addr) && !_write_data(data, size)) {
        return false;
    }

    return true;
}

bool I2CDev::send16(uint8_t devAddr, uint16_t addr, const void *data, std::size_t size) noexcept {
    if (!_set_slave_address(devAddr) && !_set_pointer16(addr) && !_write_data(data, size)) {
        return false;
    }
}

std::unique_ptr<uint8_t> I2CDev::read8(uint8_t devAddr, uint8_t addr, std::size_t size) noexcept {
    if (!_set_slave_address(devAddr) && !_set_pointer8(addr)) {
        return nullptr;
    }

    std::unique_ptr<uint8_t> alloc{new uint8_t[size]};
    
    if (!_read_data(alloc.get(), size)) {
        return nullptr;
    }

    return alloc;
}

std::unique_ptr<uint8_t> I2CDev::read16(uint8_t devAddr, uint16_t addr, std::size_t size) noexcept {
    if (!_set_slave_address(devAddr) && !_set_pointer16(addr)) {
        return nullptr;
    }

    std::unique_ptr<uint8_t> alloc{new uint8_t[size]};
    
    if (!_read_data(alloc.get(), size)) {
        return nullptr;
    }

    return alloc;
}

bool I2CDev::read8(uint8_t devAddr, uint8_t addr, uint8_t *dataBuffer, std::size_t size) noexcept {
    if (!_set_slave_address(devAddr) && !_set_pointer8(addr) && !_read_data(dataBuffer, size)) {
        return false;
    }
    
    return true;
}

bool I2CDev::read16(uint8_t devAddr, uint16_t addr, uint8_t *dataBuffer, std::size_t size) noexcept {
    if (!_set_slave_address(devAddr) && !_set_pointer16(addr) && !_read_data(dataBuffer, size)) {
        return false;
    }

    return true;
}

bool I2CDev::is_initiated() const {
    if (_fd == -1) {
        return false;
    }
    return true;
}

bool I2CDev::initiate(std::string_view fileName) noexcept {
    _fileName = fileName;
    return _init_file();
}

bool I2CDev::_init_file() noexcept {
    if ((_fd = open(_fileName.data(), O_RDWR)) == 0) {
        LOG_WARN("Unable to open file: %s. Errno value is %d", _fileName.data(), errno);
        return false;
    }
}

bool I2CDev::_set_slave_address(uint8_t devAddr) noexcept {
    if (devAddr == _lastSlaveAddress) {
        return true;
    }

    if (ioctl(_fd, I2C_SLAVE, static_cast<int>(devAddr)) == -1) {
        LOG_WARN("Unable to set slave address %d. Errno value is %d.", devAddr, errno);
        return false;
    }
    _lastSlaveAddress = devAddr;
    return true;
}

bool I2CDev::_set_pointer8(uint8_t addr) noexcept {
    if (write(_fd, &addr, 1) == -1) {
        LOG_WARN("Unable to set pointer on slave addr: %d. Errno value is %d", _lastSlaveAddress, errno);
        return false;
    }
    return true;
}

bool I2CDev::_set_pointer16(uint16_t addr) noexcept {
    uint8_t buff[2];
    buff[1] = addr >> 8;
    buff[2] = addr & 0xFF;
    if (write(_fd, buff, 2) == -1) {
        LOG_WARN("Unable to set pointer on slave addr: %d. Errno value is %d", _lastSlaveAddress, errno);
        return false;
    }
    return true;
}

bool I2CDev::_write_data(const void* data, std::size_t size) noexcept {
    int ret;
    if ((ret = write(_fd, data, size)) == -1) {
        LOG_WARN("Unable to write value. Errno value is %d." errno);
        return false;
    }
    if (ret != size) {
        LOG_WARN("Whole value could not send.");
        return false;
    }
    LOG_INFO("Data sent successfully.");
    return true;
}

bool I2CDev::_read_data(uint8_t* data, std::size_t size) noexcept {
    int ret;
    if ((ret = read(_fd, data, size)) == -1) {
        LOG_WARN("Unable to read data. Errno value is %d.", errno);
        return false;
    }
    if (ret != size) {
        LOG_WARN("Whole data chuck could not read.");
        return false;
    }
    LOG_INFO("Data read successfully.");
    return true;
}