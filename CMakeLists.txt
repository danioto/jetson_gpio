# Cmake
cmake_minimum_required (VERSION 2.6)
project(jetson_gpio)

# libgpio
set(LIBGPIO_HEADER "/usr/local/include/gpio.h")
set(LIBGPIO_LIBRARY "/usr/local/lib/libgpio.so")

IF(EXISTS ${LIBGPIO_HEADER} AND EXISTS ${LIBGPIO_LIBRARY})
  message("-- libgpio found!")
ELSE()
  message(FATAL_ERROR "* libgpio not found!")
ENDIF()

# Add executable
add_executable(jetson_gpio src/main.cpp)
target_link_libraries(jetson_gpio ${LIBGPIO_LIBRARY})
