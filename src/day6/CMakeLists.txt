add_executable(day6 day6.cc)
target_compile_features(day6 PRIVATE cxx_std_17)

target_include_directories(day6 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day6 PRIVATE fmt utils)
