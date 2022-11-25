add_executable(day16 day16.cc)
target_compile_features(day16 PRIVATE cxx_std_17)

target_include_directories(day16 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day16 PRIVATE fmt utils)
