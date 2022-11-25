add_executable(day4 day4.cc)
target_compile_features(day4 PRIVATE cxx_std_17)

target_include_directories(day4 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day4 PRIVATE fmt utils)
