# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(led_example C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# The driver lives in the shared drivers folder, two levels up
set(DRIVERS_DIR ${CMAKE_CURRENT_LIST_DIR}/../../drivers)

add_executable(led_example
        main.c
        ${DRIVERS_DIR}/led.c)

pico_set_program_name(led_example "led_example")
pico_set_program_version(led_example "0.1")

pico_enable_stdio_uart(led_example 0)
pico_enable_stdio_usb(led_example 1)

target_link_libraries(led_example
        pico_stdlib)

target_include_directories(led_example PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${DRIVERS_DIR}
)

pico_add_extra_outputs(led_example)
