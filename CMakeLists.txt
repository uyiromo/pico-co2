cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(test_project C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# test configs
add_executable(test test.c)
pico_enable_stdio_usb(test 1)
pico_enable_stdio_uart(test 0)
pico_add_extra_outputs(test)
target_link_libraries(test pico_stdlib)

# main configs
add_executable(main main.c)
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)
pico_add_extra_outputs(main)
target_link_libraries(main led sensor pico_stdlib pico_multicore)
target_include_directories(main
    PRIVATE led
    PRIVATE sensor
)



# led
add_subdirectory(led)

# sensor
add_subdirectory(sensor)
