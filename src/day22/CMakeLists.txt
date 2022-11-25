add_executable(day22 day22.cc)
target_compile_features(day22 PRIVATE cxx_std_17)

target_include_directories(day22 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day22 PRIVATE fmt utils)
