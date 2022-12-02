add_executable(day02 day2.cc)
target_compile_features(day02 PRIVATE cxx_std_17)

target_include_directories(day02 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day02 PRIVATE fmt utils)
