add_executable(day11 day11.cc)
target_compile_features(day11 PRIVATE cxx_std_17)

target_include_directories(day11 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day11 PRIVATE fmt utils)
