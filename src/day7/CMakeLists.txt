add_executable(day7 day7.cc)
target_compile_features(day7 PRIVATE cxx_std_17)

target_include_directories(day7 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day7 PRIVATE fmt utils)
