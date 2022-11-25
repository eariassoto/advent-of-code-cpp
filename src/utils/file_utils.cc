// Copyright 2022 Emmanuel Arias Soto
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.
#include "utils/file_utils.h"

#include <fmt/core.h>

#include <algorithm>
#include <fstream>

std::vector<std::string> ReadFile(const std::string &file_path)
{
    std::vector<std::string> res;
    // Open the File
    std::ifstream in(file_path.c_str());
    if (!in)
    {
        fmt::print(stderr, "Cannot open file: {}.", file_path);
        return res;
    }

    std::string line;
    while (std::getline(in, line))
    {
        res.emplace_back();
        line.swap(res.back());
    }

    return res;
}
