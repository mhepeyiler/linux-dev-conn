add_library(Logger
            INTERFACE
            ALIAS
            logger::logger)

target_include_directories(Logger 
                           INTERFACE
                           "${CMAKE_CURRENT_SOURCE_DIR}/include")