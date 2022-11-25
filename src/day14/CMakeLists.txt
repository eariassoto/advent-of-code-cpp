add_executable(day14 day14.cc)
target_compile_features(day14 PRIVATE cxx_std_17)

target_include_directories(day14 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day14 PRIVATE fmt utils)
