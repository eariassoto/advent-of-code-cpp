// Copyright 2022 Emmanuel Arias Soto
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.
#include "paths.h"
#include "utils/file_utils.h"

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <array>
#include <numeric>
#include <string>
#include <vector>

void FindSignalStrength(const std::vector<std::string>& input)
{
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

    for (const std::string& line : input) {
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
        // fmt::print("Adding {}\n", second_half);
        reg_x += std::stoi(second_half);
    }
    fmt::print("{}\n", std::accumulate(freqs.begin(), freqs.end(), 0));
}

int main()
{
    std::vector<std::string> input = ReadFile(DAY_10_INPUT);
    // FindSignalStrength(input);

    std::array<std::array<char, 40>, 6> screen;
    for (auto& screen_line : screen) {
        screen_line.fill('#');
    }

    int reg_x = 1;
    int cycle = 0;
    while (cycle < 6 * 40) {
        const std::string& instr = input.front();
        if (instr == "noop") {
            const int curr_line = cycle / 40;
            const int curr_pixel = cycle % 40;

            char to_draw = (curr_pixel >= reg_x - 1 && curr_pixel <= reg_x + 1)
                               ? '#'
                               : '.';
            screen[curr_line][curr_pixel] = to_draw;

            ++cycle;
            input.erase(input.begin());
            continue;
        }
        // addx
        const int c1_line = cycle / 40;
        const int c1_pixel = cycle % 40;
        char c1_draw =
            (c1_pixel >= reg_x - 1 && c1_pixel <= reg_x + 1) ? '#' : '.';
        screen[c1_line][c1_pixel] = c1_draw;
        ++cycle;

        const int c2_line = cycle / 40;
        const int c2_pixel = cycle % 40;
        char c2_draw =
            (c2_pixel >= reg_x - 1 && c2_pixel <= reg_x + 1) ? '#' : '.';
        screen[c2_line][c2_pixel] = c2_draw;
        ++cycle;

        auto pos = instr.find(' ');
        auto second_half = instr.substr(pos + 1);
        // fmt::print("Adding {}\n", second_half);
        reg_x += std::stoi(second_half);
        input.erase(input.begin());
        // if (curr_line % 2 == 0) {
        //     screen[curr_line][curr_pixel] = curr_pixel % 2 == 0 ? '$' : '*';
        // }
    }

    for (auto& screen_line : screen) {
        fmt::print("{}\n", fmt::join(screen_line, ""));
    }
    return 0;
}