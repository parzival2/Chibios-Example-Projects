# Set Headers needed
set(HEADERS
    chconf.h
    halconf.h
    mcuconf.h
    usbcfg.h
    etl_profile.h
    #ROS
    ChibiOSHardware.h
    ros.h)

set(SOURCES
    usbcfg.c
    main.cpp
    #ROS
    ${PROJECT_SOURCE_DIR}/Libraries/ros_lib/time.cpp
    ${PROJECT_SOURCE_DIR}/Libraries/ros_lib/duration.cpp
    README.md)

# For printing float values
add_definitions("-DCHPRINTF_USE_FLOAT")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Libraries/ros_lib)
include_directories(${PROJECT_SOURCE_DIR}/Libraries/etlcpp/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
add_chibios_executable(ETL_Cpp
                       ${HEADERS}
                       ${SOURCES})
