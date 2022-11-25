add_executable(day19 day19.cc)
target_compile_features(day19 PRIVATE cxx_std_17)

target_include_directories(day19 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day19 PRIVATE fmt utils)
