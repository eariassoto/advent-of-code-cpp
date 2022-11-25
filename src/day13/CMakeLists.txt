add_executable(day13 day13.cc)
target_compile_features(day13 PRIVATE cxx_std_17)

target_include_directories(day13 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day13 PRIVATE fmt utils)
