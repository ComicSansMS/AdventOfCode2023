add_library(04_scratchcards STATIC)
target_sources(04_scratchcards
    PUBLIC
    FILE_SET CXX_MODULES
    BASE_DIRS ${CMAKE_CURRENT_LIST_DIR}
    FILES
    ${CMAKE_CURRENT_LIST_DIR}/scratchcards.cpp
)
target_link_libraries(04_scratchcards PUBLIC std::mdspan)

add_executable(advent04 advent04.cpp)
target_link_libraries(advent04 PUBLIC 04_scratchcards)

file(COPY input DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(TARGET Catch)
    add_executable(04_scratchcards_test scratchcards.t.cpp)
    target_link_libraries(04_scratchcards_test PUBLIC Catch 04_scratchcards)
    add_test(NAME TestAdvent04 COMMAND 04_scratchcards_test)
    enable_coverage(04_scratchcards)
endif()
