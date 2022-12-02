add_executable(day09 day9.cc)
target_compile_features(day09 PRIVATE cxx_std_17)

target_include_directories(day09 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day09 PRIVATE fmt utils)
