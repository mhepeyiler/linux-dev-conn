add_executable(i2c_test
               "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

 
target_include_directories(i2c_test
                           PRIVATE
                           "${SRC_SOURCE_DIR}/logger/include"
                           "${SRC_SOURCE_DIR}/i2c/include"
)

target_link_libraries(i2c_test
                      PRIVATE
                      i2c::i2c
                      logger::logger
)