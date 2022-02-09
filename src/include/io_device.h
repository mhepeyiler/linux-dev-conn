#ifndef LINUX_DEV_CONN_SRC_INCLUDE_IO_DEVICE_H
#define LINUX_DEV_CONN_SRC_INCLUDE_IO_DEVICE_H

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
};

#endif