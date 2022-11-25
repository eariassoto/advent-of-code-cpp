add_executable(day9 day9.cc)
target_compile_features(day9 PRIVATE cxx_std_17)

target_include_directories(day9 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day9 PRIVATE fmt utils)
