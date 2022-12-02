add_executable(day01 day1.cc)
target_compile_features(day01 PRIVATE cxx_std_17)

target_include_directories(day01 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day01 PRIVATE fmt utils)
