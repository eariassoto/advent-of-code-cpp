add_executable(day04 day4.cc)
target_compile_features(day04 PRIVATE cxx_std_17)

target_include_directories(day04 PRIVATE 
    ../../include
    "${PROJECT_BINARY_DIR}/include")

target_link_libraries(day04 PRIVATE fmt utils)
