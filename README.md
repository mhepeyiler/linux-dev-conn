# LinuxDevConn

A library to use in the development of a Linux-based board. It provides a C++ interface for upper-layer code baseline.

## Installation

Installation steps to use library in your project. As prerequistes, git and cmake must be installed in your system.

```bash
$ mkdir build
$ cd build
# if you want to disable log then $ cmake .. -DLOG=0
$ cmake ..
$ make
```

## Usage

Please check [example](example) folder.

### Usage with cmake 

Download this repository in your project directory. Then please update your CMakeLists.txt as shown below.

```cmake
add_subdirectory(linux-dev-conn)
target_link_libraries(MyFancyTarget i2c::i2c)
# target_link_libraries(MyFancTarget <inteded device>)
```

## Contributing

Pull requests are welcome. For major updates, please open an issue first to discuss what you are planning to add.

Please make sure that you follow general structure of code baseline.

## Licence

[MIT](LICENCE)
