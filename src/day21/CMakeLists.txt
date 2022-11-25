add_executable(day21 day21.cc)
target_compile_features(day21 PRIVATE cxx_std_17)

target_include_directories(day21 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day21 PRIVATE fmt utils)
