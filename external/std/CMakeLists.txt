cmake_minimum_required(VERSION 3.28)

project(module_std)

add_library(module_std)

target_sources(module_std PUBLIC
    FILE_SET CXX_MODULES
    FILES
    ${PROJECT_SOURCE_DIR}/module_std.cpp
)
