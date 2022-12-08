// Copyright 2022 Emmanuel Arias Soto
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.
#include "paths.h"
#include "utils/file_utils.h"

#include <fmt/core.h>

#include <string>
#include <vector>
#include <unordered_set>
#include <utility>
#include <algorithm>

struct pair_hash {
    inline std::size_t operator()(const std::pair<int, int>& v) const
    {
        return v.first * 31 + v.second;
    }
};

int main()
{
    std::vector<std::string> input = ReadFile(DAY_8_INPUT);
    // for (const std::string &line : input)
    //     fmt::print("{}\n", line);

    unsigned int map_width = input[0].size();
    unsigned int map_heigth = input.size();

    fmt::print("map w{}, h{}\n", map_width, map_heigth);

    std::unordered_set<std::pair<int, int>, pair_hash> visible_trees;

    // eval left
    for (int h = 0; h < map_heigth; ++h) {
        unsigned int aux = 0;
        for (int w = 0; w < map_width; ++w) {
            if (w == 0 || h == 0 || w == (map_width - 1) ||
                h == (map_heigth - 1)) {
                visible_trees.emplace(std::make_pair(w, h));
            }
            if (w == map_width - 1) {
                continue;
            }

            const unsigned int out_tree = input[h][w] - '0';
            aux = std::max(aux, out_tree);
            const unsigned int in_tree = input[h][w + 1] - '0';
            if (aux < in_tree) {
                fmt::print("found {} {}: {}\n", w + 1, h, in_tree);
                visible_trees.emplace(std::make_pair(w + 1, h));
            }
        }
    }

    // eval right
    for (int h = 1; h < map_heigth; ++h) {
        unsigned int aux = 0;
        for (int w = map_width - 1; w >= 0; --w) {
            if (w == 0 || h == 0 || w == (map_width - 1) ||
                h == (map_heigth - 1)) {
                visible_trees.emplace(std::make_pair(w, h));
            }
            if (w == 0) {
                continue;
            }

            const unsigned int out_tree = input[h][w] - '0';
            aux = std::max(aux, out_tree);
            const unsigned int in_tree = input[h][w - 1] - '0';
            if (aux < in_tree) {
                fmt::print("found {} {}: {}\n", w - 1, h, in_tree);
                visible_trees.emplace(std::make_pair(w - 1, h));
            }
        }
    }

    // eval top
    for (int w = 0; w < map_width; ++w) {
        unsigned int aux = 0;
        for (int h = 0; h < map_heigth; ++h) {
            if (w == 0 || h == 0 || w == (map_width - 1) ||
                h == (map_heigth - 1)) {
                visible_trees.emplace(std::make_pair(w, h));
            }
            if (h == map_heigth - 1) {
                continue;
            }

            const unsigned int out_tree = input[h][w] - '0';
            aux = std::max(aux, out_tree);
            const unsigned int in_tree = input[h + 1][w] - '0';
            if (aux < in_tree) {
                fmt::print("found {} {}: {}\n", w, h + 1, input[h + 1][w]);
                visible_trees.emplace(std::make_pair(w, h + 1));
            }
        }
    }

    // eval bottom
    for (int w = 0; w < map_width; ++w) {
        unsigned int aux = 0;
        for (int h = map_heigth - 1; h >= 0; --h) {
            if (w == 0 || h == 0 || w == (map_width - 1) ||
                h == (map_heigth - 1)) {
                visible_trees.emplace(std::make_pair(w, h));
            }
            if (h == 0) {
                continue;
            }

            const unsigned int out_tree = input[h][w] - '0';
            aux = std::max(aux, out_tree);
            const unsigned int in_tree = input[h - 1][w] - '0';
            if (aux < in_tree) {
                fmt::print("found {} {}: {}\n", w, h - 1, input[h - 1][w]);
                visible_trees.emplace(std::make_pair(w, h - 1));
            }
        }
    }
    fmt::print("{}\n", visible_trees.size());

    return 0;
}