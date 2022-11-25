add_executable(day20 day20.cc)
target_compile_features(day20 PRIVATE cxx_std_17)

target_include_directories(day20 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day20 PRIVATE fmt utils)
