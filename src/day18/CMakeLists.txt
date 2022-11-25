add_executable(day18 day18.cc)
target_compile_features(day18 PRIVATE cxx_std_17)

target_include_directories(day18 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day18 PRIVATE fmt utils)
