add_executable(day3 day3.cc)
target_compile_features(day3 PRIVATE cxx_std_17)

target_include_directories(day3 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day3 PRIVATE fmt utils)
