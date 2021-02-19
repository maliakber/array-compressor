add_executable(compressor main.cpp)
add_executable(compressor-test unit-test.cpp)

add_subdirectory(utils)

target_link_libraries(
    compressor
    utils
)

target_link_libraries(
    compressor-test
    utils
)
