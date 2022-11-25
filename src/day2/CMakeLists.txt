add_executable(day2 day2.cc)
target_compile_features(day2 PRIVATE cxx_std_17)

target_include_directories(day2 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day2 PRIVATE fmt utils)
