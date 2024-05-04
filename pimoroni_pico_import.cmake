# This file can be dropped into a project to help locate the Pimoroni Pico libraries
# It will also set up the required include and module search paths.

if (NOT PIMORONI_PICO_PATH)
    if (PIMORONI_PICO_FETCH_FROM_GIT)
        include(FetchContent)
        set(FETCHCONTENT_BASE_DIR_SAVE ${FETCHCONTENT_BASE_DIR})
        if (PIMORONI_PICO_FETCH_FROM_GIT_PATH)
            get_filename_component(FETCHCONTENT_BASE_DIR "${PIMORONI_PICO_FETCH_FROM_GIT_PATH}" REALPATH BASE_DIR "${CMAKE_SOURCE_DIR}")
        endif ()
        FetchContent_Declare(
                pimoroni_pico
                GIT_REPOSITORY https://github.com/pimoroni/pimoroni-pico
                GIT_TAG main
        )
        if (NOT pimoroni_pico)
            message("Downloading PIMORONI_PICO SDK")
            FetchContent_Populate(pimoroni_pico)
            set(PIMORONI_PICO_PATH ${pimoroni_pico_SOURCE_DIR})
        endif ()
        set(FETCHCONTENT_BASE_DIR ${FETCHCONTENT_BASE_DIR_SAVE})
    elseif(PICO_SDK_PATH AND EXISTS "${PICO_SDK_PATH}/../pimoroni-pico")
        set(PIMORONI_PICO_PATH ${PICO_SDK_PATH}/../pimoroni-pico)
        message("Defaulting PIMORONI_PICO_PATH as sibling of PICO_SDK_PATH: ${PIMORONI_PICO_PATH}")
    elseif(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/../../pimoroni-pico/")
        set(PIMORONI_PICO_PATH ${CMAKE_CURRENT_BINARY_DIR}/../../pimoroni-pico/)
    else()
        message(FATAL_ERROR "Pimoroni Pico location was not specified. Please set PIMORONI_PICO_PATH.")
    endif()
endif()

get_filename_component(PIMORONI_PICO_PATH "${PIMORONI_PICO_PATH}" REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")
if (NOT EXISTS ${PIMORONI_PICO_PATH})
    message(FATAL_ERROR "Directory '${PIMORONI_PICO_PATH}' not found")
endif ()

if (NOT EXISTS ${PIMORONI_PICO_PATH}/pimoroni_pico_import.cmake)
    message(FATAL_ERROR "Directory '${PIMORONI_PICO_PATH}' does not appear to contain the Pimoroni Pico libraries")
endif ()

message("PIMORONI_PICO_PATH is ${PIMORONI_PICO_PATH}")

set(PIMORONI_PICO_PATH ${PIMORONI_PICO_PATH} CACHE PATH "Path to the Pimoroni Pico libraries" FORCE)

include_directories(${PIMORONI_PICO_PATH})
list(APPEND CMAKE_MODULE_PATH ${PIMORONI_PICO_PATH})
