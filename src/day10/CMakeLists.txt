add_executable(day10 day10.cc)
target_compile_features(day10 PRIVATE cxx_std_17)

target_include_directories(day10 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day10 PRIVATE fmt utils)
