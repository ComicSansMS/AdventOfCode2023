add_library(03_gear_ratios STATIC)
target_sources(03_gear_ratios
    PUBLIC
    FILE_SET CXX_MODULES
    BASE_DIRS ${CMAKE_CURRENT_LIST_DIR}
    FILES
    ${CMAKE_CURRENT_LIST_DIR}/gear_ratios.cpp
)
target_link_libraries(03_gear_ratios PUBLIC std::mdspan)

add_executable(advent03 advent03.cpp)
target_link_libraries(advent03 PUBLIC 03_gear_ratios)

file(COPY input DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(TARGET Catch)
    add_executable(03_gear_ratios_test gear_ratios.t.cpp)
    target_link_libraries(03_gear_ratios_test PUBLIC Catch 03_gear_ratios)
    add_test(NAME TestAdvent03 COMMAND 03_gear_ratios_test)
    enable_coverage(03_gear_ratios)
endif()
