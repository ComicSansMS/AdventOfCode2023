add_library(01_trebuchet STATIC)
target_sources(01_trebuchet
    PUBLIC
    FILE_SET CXX_MODULES
    BASE_DIRS ${CMAKE_CURRENT_LIST_DIR}
    FILES
    ${CMAKE_CURRENT_LIST_DIR}/trebuchet.cpp
)

add_executable(advent01 advent01.cpp)
target_link_libraries(advent01 PUBLIC 01_trebuchet)

file(COPY input DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(TARGET Catch)
    add_executable(01_trebuchet_test trebuchet.t.cpp)
    target_link_libraries(01_trebuchet_test PUBLIC Catch 01_trebuchet)
    add_test(NAME TestAdvent01 COMMAND 01_trebuchet_test)
    enable_coverage(01_trebuchet)
endif()
