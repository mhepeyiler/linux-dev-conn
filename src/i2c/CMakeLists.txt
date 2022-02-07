add_library(I2C
            "${CMAKE_CURRENT_SOURCE_DIR}/i2c_dev.cpp"
)

target_include_directories(I2C
                           PUBLIC
                           "${CMAKE_CURRENT_SOURCE_DIR}/include"
                           PRIVATE
                           "${SRC_SOURCE_DIR}/logger/include"
)

target_link_libraries(I2C
                     PRIVATE
                     logger::logger
)

add_library(i2c::i2c ALIAS I2C)