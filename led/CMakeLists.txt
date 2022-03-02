cmake_minimum_required(VERSION 3.13)
include(../pico_sdk_import.cmake)

project(lib_led C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# Configurations for led.a
add_library(led STATIC led.c)
target_link_libraries(led pico_stdlib)

# Configurations for led_test
add_executable(led_test led_test.c)
pico_enable_stdio_usb(led_test 1)
pico_enable_stdio_uart(led_test 0)
pico_add_extra_outputs(led_test)
target_link_libraries(led_test led pico_stdlib pico_multicore)
