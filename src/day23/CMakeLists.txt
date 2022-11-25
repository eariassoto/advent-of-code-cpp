add_executable(day23 day23.cc)
target_compile_features(day23 PRIVATE cxx_std_17)

target_include_directories(day23 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day23 PRIVATE fmt utils)
