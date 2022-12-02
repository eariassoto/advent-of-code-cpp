add_executable(day07 day7.cc)
target_compile_features(day07 PRIVATE cxx_std_17)

target_include_directories(day07 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day07 PRIVATE fmt utils)
