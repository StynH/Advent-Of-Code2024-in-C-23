cmake_minimum_required(VERSION 3.20)
project(advent_of_code
        VERSION 1.0
        DESCRIPTION "Advent of Code 2024"
        LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -Wformat=2
        -Wno-unused-parameter
        -Wshadow
        -Wwrite-strings
        -Wstrict-prototypes
        -Wold-style-definition
        -Wredundant-decls
        -Wnested-externs
        -Wmissing-include-dirs
        $<$<CONFIG:Debug>:-g3>
        $<$<CONFIG:Release>:-O3>
)

function(add_aoc_day DAY)
    set(TARGET_NAME "day${DAY}")
    set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${DAY}")

    if(EXISTS "${SOURCE_DIR}")
        file(GLOB DAY_SOURCES "${SOURCE_DIR}/*.c")
        if(DAY_SOURCES)
            add_executable(${TARGET_NAME} ${DAY_SOURCES})

            target_include_directories(${TARGET_NAME} PRIVATE
                    ${SOURCE_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}/common
            )

            set_target_properties(${TARGET_NAME} PROPERTIES
                    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/day${DAY}"
            )
        endif()
    endif()
endfunction()

add_library(common INTERFACE)
target_include_directories(common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/common)

foreach(DAY RANGE 1 25)
    if(DAY LESS 10)
        set(DAY_FORMATTED "0${DAY}")
    else()
        set(DAY_FORMATTED "${DAY}")
    endif()
    add_aoc_day(${DAY_FORMATTED})
endforeach()