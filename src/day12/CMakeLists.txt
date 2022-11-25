add_executable(day12 day12.cc)
target_compile_features(day12 PRIVATE cxx_std_17)

target_include_directories(day12 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day12 PRIVATE fmt utils)
