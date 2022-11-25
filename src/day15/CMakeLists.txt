add_executable(day15 day15.cc)
target_compile_features(day15 PRIVATE cxx_std_17)

target_include_directories(day15 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day15 PRIVATE fmt utils)
