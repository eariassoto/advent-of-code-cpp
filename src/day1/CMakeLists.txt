add_executable(day1 day1.cc)
target_compile_features(day1 PRIVATE cxx_std_17)

target_include_directories(day1 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day1 PRIVATE fmt utils)
