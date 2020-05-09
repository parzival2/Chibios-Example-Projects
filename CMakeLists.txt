cmake_minimum_required(VERSION 3.0.0)
project(Chibios_Learning VERSION 0.1.0)

# Set the board file

set(CHIBIOS_BOARD_CMAKE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Chibios_18.2.x/os/hal/boards/ST_STM32F4_DISCOVERY/stm32f4discboard.cmake)

# Set the toolchain
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Chibios_18.2.x/toolchain.cmake)

if(CMAKE_BUILD_TYPE MATCHES Release)
    add_definitions("-DOSAL_DBG_ENABLE_ASSERTS=false -DOSAL_DBG_ENABLE_CHECKS=false")
else()
    add_definitions("-DOSAL_DBG_ENABLE_ASSERTS=true -DOSAL_DBG_ENABLE_CHECKS=true")
endif()

# Include chibios
include(${CMAKE_CURRENT_SOURCE_DIR}/Chibios_18.2.x/chibios.cmake)
# For printing float values
add_definitions("-DCHPRINTF_USE_FLOAT")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

### Events
option(BUILD_CHIBIOS_EVENTS_EXAMPLE "Build chibios events example" TRUE)
if(BUILD_CHIBIOS_EVENTS_EXAMPLE)
    add_subdirectory(Events_Chibios)
endif()

### ADC
option(BUILD_CHIBIOS_ADC_EXAMPLE "Build chibios ADC example" TRUE)
if(BUILD_CHIBIOS_ADC_EXAMPLE)
    add_subdirectory(ADC_Steering)
endif()

### Thread_Thread_Communication
option(BUILD_CHIBIOS_THREAD_THREAD_COMMUNICATION "Build thread to thread communication" TRUE)
if(BUILD_CHIBIOS_THREAD_THREAD_COMMUNICATION)
    add_subdirectory(Thread_Thread_Communication)
endif()

### Servo control
option(BUILD_CHIBIOS_SERVO_CONTROL "Build servo control" TRUE)
if(BUILD_CHIBIOS_SERVO_CONTROL)
    add_subdirectory(Servo_Control)
endif()

### ETL Cpp
option(BUILD_CHIBIOS_ETL_CPP "Build etl cpp project" TRUE)
if(BUILD_CHIBIOS_ETL_CPP)
    add_subdirectory(Chibios_ETLCpp)
endif()

