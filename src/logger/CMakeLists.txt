add_library(Logger
            INTERFACE
)

target_include_directories(Logger 
                           INTERFACE
                           "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_library(logger::logger ALIAS Logger)