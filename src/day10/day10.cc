// Copyright 2022 Emmanuel Arias Soto
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.
#include "paths.h"
#include "utils/file_utils.h"

#include <fmt/core.h>

#include <numeric>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> input = ReadFile(DAY_10_INPUT);

    int reg_x = 1;
    unsigned int cycles = 0;
    std::vector<int> freqs;
    std::vector<int> cycles_list;
    cycles_list.push_back(20);
    cycles_list.push_back(60);
    cycles_list.push_back(100);
    cycles_list.push_back(140);
    cycles_list.push_back(180);
    cycles_list.push_back(220);

    for (const std::string &line : input) {
        if (cycles_list.empty()) break;

        if (cycles == cycles_list[0]) {
            freqs.push_back(cycles_list[0] * reg_x);
            cycles_list.erase(cycles_list.begin());
        }

        if (line == "noop") {
            ++cycles;
            continue;
        }

        // addx
        // Peek in the future
        if ((cycles + 2) >= cycles_list[0]) {
            freqs.push_back(cycles_list[0] * reg_x);
            cycles_list.erase(cycles_list.begin());
        }

        // Complete instrction
        cycles += 2;

        auto pos = line.find(' ');
        auto second_half = line.substr(pos + 1);
        fmt::print("Adding {}\n", second_half);
        reg_x += std::stoi(second_half);
    }
    fmt::print("{}\n", std::accumulate(freqs.begin(), freqs.end(), 0));

    return 0;
}