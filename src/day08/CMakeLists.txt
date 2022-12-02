add_executable(day08 day8.cc)
target_compile_features(day08 PRIVATE cxx_std_17)

target_include_directories(day08 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day08 PRIVATE fmt utils)
