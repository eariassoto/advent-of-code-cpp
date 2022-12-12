// Copyright 2022 Emmanuel Arias Soto
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.
#include "paths.h"
#include "utils/file_utils.h"

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

using Visited = std::vector<std::pair<unsigned int, unsigned int>>;

struct Map {
    Map(const std::vector<std::string>& input)
        : Input(input), MapWidth(input[0].size()), MapHeight(input.size())
    {
    }

    void foo(unsigned int x, unsigned int y, Visited visited,
             unsigned int steps)
    {
        const char curr_letter = Input[y][x];
        if (curr_letter == 'E') {
            // fmt::print("found a way! steps {}\n", steps);
            if (steps < MinSteps) {
                MinSteps = steps;
                Visited = visited;
            }
            return;
        }

        visited.emplace_back(std::make_pair(x, y));

        // can go up
        if (y > 0) {
            if (Input[y - 1][x] <= curr_letter + 1) {
                if (std::find_if(visited.begin(), visited.end(),
                                 [x, y](const auto& p) {
                                     return p.first == x && p.second == y - 1;
                                 }) == visited.end()) {
                    // fmt::print("can go up {},{}\n", x, y);
                    foo(x, y - 1, visited, steps + 1);
                }
            }
        }
        // can go down
        if (y < MapHeight - 1) {
            if (Input[y + 1][x] <= curr_letter + 1) {
                if (std::find_if(visited.begin(), visited.end(),
                                 [x, y](const auto& p) {
                                     return p.first == x && p.second == y + 1;
                                 }) == visited.end()) {
                    // fmt::print("can go down {},{}\n", x, y);
                    foo(x, y + 1, visited, steps + 1);
                }
            }
        }

        // can go left
        if (x > 0) {
            if (Input[y][x - 1] <= curr_letter + 1) {
                if (std::find_if(visited.begin(), visited.end(),
                                 [x, y](const auto& p) {
                                     return p.first == x - 1 && p.second == y;
                                 }) == visited.end()) {
                    // fmt::print("can go up {},{}\n", x, y);
                    foo(x - 1, y, visited, steps + 1);
                }
            }
        }
        // can go down
        if (x < MapWidth - 1) {
            if (Input[y][x + 1] <= curr_letter + 1) {
                if (std::find_if(visited.begin(), visited.end(),
                                 [x, y](const auto& p) {
                                     return p.first == x + 1 && p.second == y;
                                 }) == visited.end()) {
                    // fmt::print("can go down {},{}\n", x, y);
                    foo(x + 1, y, visited, steps + 1);
                }
            }
        }
    }

    const std::vector<std::string>& Input;
    const unsigned int MapWidth;
    const unsigned int MapHeight;

    unsigned int MinSteps = std::numeric_limits<unsigned int>::max();
    Visited Visited;
};

int main()
{
    std::vector<std::string> input = ReadFile(DAY_12_INPUT);
    for (const std::string& line : input) fmt::print("{}\n", line);

    const unsigned int map_width = input[0].size();
    const unsigned int map_height = input.size();

    unsigned int curr_x = 0;
    unsigned int curr_y = 0;
    for (int h = 0; h < map_height; ++h) {
        for (int w = 0; w < map_width; ++w) {
            if (input[h][w] == 'S') {
                curr_x = w;
                curr_y = h;
                goto cont;
            }
        }
    }
cont:
    fmt::print("{} {}\n", curr_x, curr_y);
    input[curr_y][curr_x] = 'a';

    Map m(input);
    m.foo(curr_x, curr_y, {}, 0);

    fmt::print("steps: {}, visited: {}\n", m.MinSteps,
               fmt::join(m.Visited, "-"));

    return 0;
}