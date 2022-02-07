#ifndef LINUX_DEV_CONN_SRC_INCLUDE_IO_DEVICE_H
#define LINUX_DEV_CONN_SRC_INCLUDE_IO_DEVICE_H

class IODevice {
public:
    virtual void open() = 0;
    virtual void close() = 0;
};

#endif