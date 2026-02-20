cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME F429I_DISC1_miniProject)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C CXX ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)
add_subdirectory(Drivers/ILI9341)
add_subdirectory(Drivers/STMPE811)
add_subdirectory(Drivers/SDRAM)
add_subdirectory(Drivers/CharacterLCD)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    ${PROJECT_SOURCE_DIR}/App/Tasks/mainTask/Src/mainTask.cpp
    ${PROJECT_SOURCE_DIR}/App/Tasks/touchPanelTask/Src/touchPanelTask.cpp
    ${PROJECT_SOURCE_DIR}/App/Tasks/mnistTask/Src/mnistTask.cpp

    ${PROJECT_SOURCE_DIR}/App/Interrupts/Src/Interrupts.cpp

    ${PROJECT_SOURCE_DIR}/App/Common/Src/MutexGuard.cpp

    ${PROJECT_SOURCE_DIR}/Middlewares/MNIST_model/Src/MNIST_model.cpp
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    ${PROJECT_SOURCE_DIR}/App/Common/Inc

    ${PROJECT_SOURCE_DIR}/App/Tasks/mainTask/Inc
    ${PROJECT_SOURCE_DIR}/App/Tasks/touchPanelTask/Inc
    ${PROJECT_SOURCE_DIR}/App/Tasks/mnistTask/Inc

    ${PROJECT_SOURCE_DIR}/App/Interrupts/Inc

    ${PROJECT_SOURCE_DIR}/Middlewares/MNIST_model/Inc
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Enable float formatting in printf (newlib-nano)
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    "LINKER:-u,_printf_float"
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
    ili9341
    stmpe811
    sdramIS42S16400J
    character_lcd
)
