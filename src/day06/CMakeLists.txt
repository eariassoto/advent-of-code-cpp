add_executable(day06 day6.cc)
target_compile_features(day06 PRIVATE cxx_std_17)

target_include_directories(day06 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day06 PRIVATE fmt utils)
