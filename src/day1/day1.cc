// Copyright 2022 Emmanuel Arias Soto
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.
#include "paths.h"
#include "utils/file_utils.h"

#include <fmt/core.h>

#include <string>
#include <vector>

int main()
{
    std::vector<std::string> input = ReadFile(DAY_1_INPUT);
    for (const std::string &line : input)
        fmt::print("{}\n", line);

    return 0;
}