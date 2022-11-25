add_executable(day8 day8.cc)
target_compile_features(day8 PRIVATE cxx_std_17)

target_include_directories(day8 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day8 PRIVATE fmt utils)
