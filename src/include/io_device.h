#ifndef LINUX_DEV_CONN_SRC_INCLUDE_IO_DEVICE_H
#define LINUX_DEV_CONN_SRC_INCLUDE_IO_DEVICE_H

#include <string_view>

/**
 * @brief Interface class for digital I/O functionalities.
 * 
 */
class IODevice {
public:

    /**
     * @brief Opens the pin
     * 
     * @return true if the operation is succesful
     */
    virtual bool open() = 0;
    
    /**
     * @brief Closes the pin
     * 
     * @return true if the operation is succesful.
     */
    virtual bool close() = 0;

    /**
     * @brief Set the file name of the connection
     * 
     * @param fileName file name to open
     */
    virtual void set_file(std::string_view fileName) noexcept = 0;
};

#endif