add_executable(day25 day25.cc)
target_compile_features(day25 PRIVATE cxx_std_17)

target_include_directories(day25 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day25 PRIVATE fmt utils)
