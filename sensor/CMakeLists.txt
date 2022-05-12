cmake_minimum_required(VERSION 3.13)
include(../pico_sdk_import.cmake)

project(lib_sensor C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# Configurations for sensor.a
add_library(sensor STATIC sensor.c)
target_link_libraries(sensor pico_stdlib)

# Configurations for sensor_test
add_executable(sensor_test sensor_test.c)
pico_enable_stdio_usb(sensor_test 1)
pico_enable_stdio_uart(sensor_test 0)
pico_add_extra_outputs(sensor_test)
target_link_libraries(sensor_test sensor pico_stdlib pico_multicore)
