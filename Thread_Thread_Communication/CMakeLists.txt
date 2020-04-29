# Set Headers needed
set(HEADERS
    chconf.h
    halconf.h
    mcuconf.h
    usbcfg.h)

set(SOURCES
    usbcfg.c
    main.cpp
    README.md)

# For printing float values
add_definitions("-DCHPRINTF_USE_FLOAT")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
add_chibios_executable(Thread_Thread_Communication
                       ${HEADERS}
                       ${SOURCES})

add_custom_command(TARGET Thread_Thread_Communication
# Run after all other rules within the target have been executed
POST_BUILD
COMMAND ${TOOLCHAIN_BIN_DIR}/arm-none-eabi-size -A ${CMAKE_CURRENT_BINARY_DIR}/Thread_Thread_Communication.elf
COMMENT "This command will be executed after building bar"
VERBATIM
)
