// Copyright 2022 Emmanuel Arias Soto
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.
#include "paths.h"

#include <fmt/core.h>

#include <fstream>
#include <unordered_set>
#include <string>
#include <cassert>

unsigned int FindFirstUniqueSequence(const std::string& input,
                                     unsigned int sequence_size)
{
    std::unordered_set<char> marker_set;
    for (int i = 0; i < input.size() - sequence_size - 1; ++i) {
        for (int j = 0; j < sequence_size; ++j) {
            marker_set.emplace(input[i + j]);
        }
        if (marker_set.size() == sequence_size) {
            return i + sequence_size;
            break;
        }
        marker_set.clear();
    }
    assert(true);
    return 0;
}

int main()
{
    std::ifstream in(DAY_6_INPUT);
    if (!in) return 1;

    std::string input;
    std::getline(in, input);

    //unsigned int marker_offset = FindFirstUniqueSequence(input, 4);
    unsigned int marker_offset = FindFirstUniqueSequence(input, 14);

    fmt::print(
        "Need to process {} new characters before the first start marker.\n",
        marker_offset);

    return 0;
}