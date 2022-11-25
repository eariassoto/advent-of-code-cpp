add_executable(day24 day24.cc)
target_compile_features(day24 PRIVATE cxx_std_17)

target_include_directories(day24 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day24 PRIVATE fmt utils)
