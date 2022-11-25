# Copyright 2022 Emmanuel Arias Soto
add_library(utils file_utils.cc)
target_compile_features(utils PUBLIC cxx_std_17)

target_include_directories(utils PUBLIC ../../include)
target_link_libraries(utils PUBLIC fmt)
