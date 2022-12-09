// Copyright 2022 Emmanuel Arias Soto
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.
#include "paths.h"
#include "utils/file_utils.h"

#include <fmt/core.h>

#include <array>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

struct Knot {
    int X = 0;
    int Y = 0;
};

struct pair_hash {
    inline std::size_t operator()(const std::pair<int, int>& v) const
    {
        return v.first * 31 + v.second;
    }
};

bool UpdateTail(Knot* head, Knot* tail)
{
    const int distance_x = head->X - tail->X;
    const int distance_y = head->Y - tail->Y;
    // same row
    if (distance_y == 0) {
        // 2 steps away
        if (abs(distance_x) == 2) {
            tail->X += distance_x / 2;
            return true;
        }
        return false;
    }

    // same column
    if (distance_x == 0) {
        // 2 steps away
        if (abs(distance_y) == 2) {
            tail->Y += distance_y / 2;
            return true;
        }
        return false;
    }

    // diagonal
    if (abs(distance_x) == 2 || abs(distance_y) == 2) {
        tail->X += distance_x > 0 ? 1 : -1;
        tail->Y += distance_y > 0 ? 1 : -1;
        return true;
    }
    return false;
}

int main()
{
    std::vector<std::string> input = ReadFile(DAY_9_INPUT);

    std::array<Knot, 10> knots;
    std::unordered_set<std::pair<int, int>, pair_hash> visited_places;
    visited_places.emplace(std::make_pair(0, 0));

    for (const std::string& line : input) {
        int repeat = std::stoi(line.substr(2));

        for (int i = 0; i < repeat; ++i) {
            // fmt::print("{} {}\n", line[0], i);
            
            Knot& head = knots[0];
            if (line[0] == 'R') ++head.X;
            if (line[0] == 'L') --head.X;
            if (line[0] == 'D') ++head.Y;
            if (line[0] == 'U') --head.Y;
            // fmt::print("head {},{}\n", head.X, head.Y);
            // fmt::print("tail b {},{}\n", tail.X, tail.Y);
            for (int i = 1; i < 10; ++i) {
                const bool updated = UpdateTail(&knots[i - 1], &knots[i]);
                if (i == 9 && updated) {
                    visited_places.emplace(
                        std::make_pair(knots[9].X, knots[9].Y));
                    // fmt::print("tail visited {},{}\n", tail.X, tail.Y);
                }
            }

            // fmt::print("tail a {},{}\n", tail.X, tail.Y);
        }
    }

    fmt::print("{}\n", visited_places.size());
    return 0;
}