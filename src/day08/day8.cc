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

    int max_scenic = 0;
    for (int h = 0; h < map_heigth; ++h) {
        for (int w = 0; w < map_width; ++w) {
            // fmt::print("{},{}\n", w, h);
            if (w == 0 || h == 0 || w == (map_width - 1) ||
                h == (map_heigth - 1)) {
                continue;
            }
            int scenic = 1;
            // left
            int aux_l = w - 1;
            while (true) {
                if (aux_l == 0 || input[h][aux_l] >= input[h][w]) {
                    fmt::print("{}\n", aux_l);
                    scenic *= w - aux_l;
                    break;
                }
                --aux_l;
            }

            // right
            int aux_r = w + 1;
            while (true) {
                if (aux_r == map_width - 1 || input[h][aux_r] >= input[h][w]) {
                    scenic *= aux_r - w;
                    fmt::print("{}\n", aux_r);
                    break;
                }
                ++aux_r;
            }

            // top
            int aux_t = h - 1;
            while (true) {
                if (aux_t == 0 || input[aux_t][w] >= input[h][w]) {
                    fmt::print("{}\n", aux_t);
                    scenic *= h - aux_t;
                    break;
                }
                --aux_t;
            }

            // bottom
            int aux_b = h + 1;
            while (true) {
                if (aux_b == map_heigth - 1 || input[aux_b][w] >= input[h][w]) {
                    scenic *= aux_b - h;
                    fmt::print("{}\n", aux_b);
                    break;
                }
                ++aux_b;
            }

            fmt::print("scenic: {}\n", scenic);
            max_scenic = std::max(max_scenic, scenic);
        }
    }
    fmt::print("max scenic: {}\n", max_scenic);

    return 0;
}