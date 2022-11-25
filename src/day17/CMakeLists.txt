add_executable(day17 day17.cc)
target_compile_features(day17 PRIVATE cxx_std_17)

target_include_directories(day17 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day17 PRIVATE fmt utils)
