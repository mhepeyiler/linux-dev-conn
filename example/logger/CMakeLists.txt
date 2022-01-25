add_executable(logger
               main.cpp
)


target_link_libraries(logger
                      PRIVATE
                      logger::logger
)