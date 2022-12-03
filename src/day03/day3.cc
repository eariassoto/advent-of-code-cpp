// Copyright 2022 Emmanuel Arias Soto
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.
#include "paths.h"
#include "utils/file_utils.h"

#include <fmt/core.h>

#include <fstream>
#include <string>
#include <unordered_set>

int main()
{
    // Open the File
    std::ifstream in(DAY_3_INPUT);
    if (!in) {
        fmt::print(stderr, "Cannot open file.");
        return 0;
    }

    unsigned int priority_sum = 0;

    std::unordered_set<char> items_map;
    std::string line;
    while (std::getline(in, line)) {
        items_map.clear();
        //fmt::print("{}\n", line);
        for (int i = 0; i < line.size() / 2; ++i) {
            items_map.insert(line[i]);
        }
        for (int i = line.size() / 2; i < line.size(); ++i) {
            if (items_map.find(line[i]) != items_map.end()) {
                //fmt::print("{}\n", line[i]);
                priority_sum += (line[i] >= 'a') ? (line[i] - 'a' + 1)
                                                 : (line[i] - 'A' + 27);
                break;
            }
        }
    }
    fmt::print("The sum of priorities is: {}\n", priority_sum);

    return 0;
}