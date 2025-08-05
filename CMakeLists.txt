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
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(lab-tempo C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(lab-tempo
    src/ms5637_02ba03/ms5637.c
    src/ssd1306/ssd1306.c
    src/main.c
    # src/main_exemplos/Ex1_leitura.c
    # src/main_exemplos/Ex2_barometro.c
    # src/main_exemplos/Ex3_varBarometrica.c
    # src/main_exemplos/Ex4_ajustepressao.c

    # src/rotina_test/test_ms5637.c
)

pico_set_program_name(lab-tempo "lab-tempo")
pico_set_program_version(lab-tempo "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(lab-tempo 1)
pico_enable_stdio_usb(lab-tempo 1)

# Add the standard library to the build
target_link_libraries(lab-tempo 
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(lab-tempo PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/src/ms5637_02ba03
        ${CMAKE_CURRENT_LIST_DIR}/src/ssd1306
)

# Add any user requested libraries
target_link_libraries(lab-tempo
        hardware_i2c
        hardware_gpio
        m  # Biblioteca matemática para cálculos do sensor
        )

pico_add_extra_outputs(lab-tempo)