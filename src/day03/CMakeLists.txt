add_executable(day03 day3.cc)
target_compile_features(day03 PRIVATE cxx_std_17)

target_include_directories(day03 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day03 PRIVATE fmt utils)
