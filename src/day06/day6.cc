// Copyright 2022 Emmanuel Arias Soto
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.
#include "paths.h"

#include <fmt/core.h>

#include <fstream>
#include <unordered_set>
#include <string>

int main()
{
    std::ifstream in(DAY_6_INPUT);
    if (!in) return 1;

    std::string input;
    std::getline(in, input);

    unsigned int marker_offset = 0;
    std::unordered_set<char> marker_set;
    for (int i = 0; i < input.size() - 3; ++i) {
        marker_set.emplace(input[i]);
        marker_set.emplace(input[i + 1]);
        marker_set.emplace(input[i + 2]);
        marker_set.emplace(input[i + 3]);
        if (marker_set.size() == 4) {
            marker_offset = i + 4;
            break;
        }
        marker_set.clear();
    }

    fmt::print(
        "Need to process {} new characters before the first start marker.\n",
        marker_offset);

    return 0;
}