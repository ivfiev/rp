cmake_minimum_required(VERSION 3.12)

set(NAME wip)

include(pico_sdk_import.cmake)
include(pimoroni_pico_import.cmake)

project(${NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_BOARD pico_w)

pico_sdk_init()

add_executable(${NAME}
        main.cpp
        log.cpp
        graphics.cpp
        functions.h
)

include(common/pimoroni_i2c)
include(common/pimoroni_bus)
include(libraries/bitmap_fonts/bitmap_fonts)
include(libraries/hershey_fonts/hershey_fonts)
include(libraries/pico_explorer/pico_explorer)

target_link_libraries(${NAME}
        pimoroni_i2c
        pico_explorer # <-- List libraries here!
)

pico_add_extra_outputs(${NAME})

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.uf2
        ${CMAKE_CURRENT_LIST_DIR}/README.md
        DESTINATION .
)

set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_GENERATOR "ZIP" "TGZ")
include(CPack)

pico_enable_stdio_usb(wip 1)
