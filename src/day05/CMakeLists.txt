add_executable(day05 day5.cc)
target_compile_features(day05 PRIVATE cxx_std_17)

target_include_directories(day05 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day05 PRIVATE fmt utils)
