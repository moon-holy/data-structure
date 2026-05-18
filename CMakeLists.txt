cmake_minimum_required(VERSION 3.20)
project(DataStructures
    VERSION 1.0.0
    DESCRIPTION "C++23 经典数据结构实现与演示"
    LANGUAGES CXX
)

# C++23 标准配置
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 输出目录：所有二进制文件统一输出到 build/bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# MSVC 特定配置
if(MSVC)
    add_compile_options(/std:c++latest /W4 /utf-8)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# 头文件目录
set(DATA_STRUCTURES_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
add_library(ds_include INTERFACE)
target_include_directories(ds_include INTERFACE "${DATA_STRUCTURES_INCLUDE_DIR}")

# 收集所有 demo 源文件
file(GLOB DEMO_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp")
list(SORT DEMO_SOURCES)

# 为每个 demo 创建单独的可执行目标
foreach(demo_file ${DEMO_SOURCES})
    get_filename_component(demo_name ${demo_file} NAME_WE)
    add_executable(${demo_name} ${demo_file})
    target_link_libraries(${demo_name} PRIVATE ds_include)
    set_property(TARGET ${demo_name} PROPERTY FOLDER "examples")
endforeach()

# 自定义目标：一键运行所有 demo
add_custom_target(check ALL
    COMMAND ${CMAKE_COMMAND} -E echo "========================================"
    COMMAND ${CMAKE_COMMAND} -E echo "  DataStructures - All Demos"
    COMMAND ${CMAKE_COMMAND} -E echo "========================================"
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMENT "Run 'cmake --build . --target run_all' to execute all demos"
)

foreach(demo_file ${DEMO_SOURCES})
    get_filename_component(demo_name ${demo_file} NAME_WE)
    add_custom_command(TARGET check POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "--- ${demo_name} ---"
        COMMAND "$<TARGET_FILE:${demo_name}>"
    )
endforeach()
