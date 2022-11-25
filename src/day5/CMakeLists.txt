add_executable(day5 day5.cc)
target_compile_features(day5 PRIVATE cxx_std_17)

target_include_directories(day5 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day5 PRIVATE fmt utils)
