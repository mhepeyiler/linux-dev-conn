#ifndef LINUX_DEV_CONN_SRC_INCLUDE_COMM_DEVICE_H
#define LINUX_DEV_CONN_SRC_INCLUDE_COMM_DEVICE_H

#include <memory>


/**
 * @brief Abstract class for connection devices. 
 * 
 * @details All connection classes, such as i2c, spi, must be inherited from here.
 */
class CommDevice {
public:

    /**
     * @brief Generic send method over data bus.
     * 
     * @param devAddress Device address to send data
     * @param address Register address
     * @param data Data to be send
     * @param dataSize Size of data
     * 
     * @return Returns true if the send successful
     */
    virtual bool send(uint16_t devAddress, uint16_t address, const uint8_t* data, std::size_t dataSize) noexcept = 0;

    /**
     * @brief Generic read method over data bus.
     * 
     * @details This function uses user given preallocated space to write data.
     * 
     * @param devAddress Device address to read data
     * @param address Register address
     * @param dataSize Data to be read
     * @param data Preallocated memory space to write data. If read data exceeds allocated memory space, it is undefined behaviour.
     * 
     * @return Returns true if the read is successful
     */
    virtual bool read(uint16_t devAddress, uint16_t address, std::size_t dataSize, uint8_t* data) noexcept = 0;

    /**
     * @brief Generic read method over data bus.
     * 
     * @details This function uses dynamic memory allocation to transfer data to user. 
     * 
     * @param devAddress Device address to read data
     * @param address Register address
     * @param dataSize Data to be read
     * 
     * @return If the read fails then it returns nullptr, otherwise data pointer.
     */
    virtual std::unique_ptr<uint8_t> read(uint16_t devAddress, uint16_t address, std::size_t dataSize) noexcept = 0;
};

#endif