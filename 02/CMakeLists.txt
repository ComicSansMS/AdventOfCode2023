add_library(02_cube_conundrum STATIC)
target_sources(02_cube_conundrum
    PUBLIC
    FILE_SET CXX_MODULES
    BASE_DIRS ${CMAKE_CURRENT_LIST_DIR}
    FILES
    ${CMAKE_CURRENT_LIST_DIR}/cube_conundrum.cpp
)

add_executable(advent02 advent02.cpp)
target_link_libraries(advent02 PUBLIC 02_cube_conundrum)

file(COPY input DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(TARGET Catch)
    add_executable(02_cube_conundrum_test cube_conundrum.t.cpp)
    target_link_libraries(02_cube_conundrum_test PUBLIC Catch 02_cube_conundrum)
    add_test(NAME TestAdvent02 COMMAND 02_cube_conundrum_test)
    enable_coverage(02_cube_conundrum)
endif()
