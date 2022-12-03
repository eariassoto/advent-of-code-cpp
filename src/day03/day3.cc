// Copyright 2022 Emmanuel Arias Soto
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.
#include "paths.h"
#include "utils/file_utils.h"

#include <fmt/core.h>

#include <fstream>
#include <string>
#include <unordered_set>
#include <array>
#include <cassert>

int GetPriority(char ch)
{
    if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 27;
    if (ch >= 'a' && ch <= 'z') return ch - 'a' + 1;
    assert(true);
    return 0;
}

void first_star(std::ifstream in)
{
    unsigned int priority_sum = 0;

    std::unordered_set<char> items_set;
    std::string line;
    while (std::getline(in, line)) {
        items_set.clear();
        // fmt::print("{}\n", line);
        for (int i = 0; i < line.size() / 2; ++i) {
            items_set.insert(line[i]);
        }
        for (int i = line.size() / 2; i < line.size(); ++i) {
            if (items_set.find(line[i]) != items_set.end()) {
                // fmt::print("{}\n", line[i]);
                priority_sum += GetPriority(line[i]);
                break;
            }
        }
    }
    fmt::print("The sum of priorities is: {}\n", priority_sum);
}

int main()
{
    // Open the File
    std::ifstream in(DAY_3_INPUT);
    if (!in) {
        fmt::print(stderr, "Cannot open file.");
        return 0;
    }
    // first_star(std::move(in));
    int priority_sum = 0;
    int group_member_count = 0;
    std::string line;
    std::array<int, 52> items_set_1;
    std::array<int, 52> items_set_2;
    std::array<int, 52> items_set_3;
    items_set_1.fill(0);
    items_set_2.fill(0);
    items_set_3.fill(0);

    std::array<std::array<int, 52>*, 3> set_list = {&items_set_1, &items_set_2,
                                                    &items_set_3};
    while (std::getline(in, line)) {
        if (group_member_count == 3) {
            for (int i = 0; i < 52; ++i) {
                const bool is_badge = items_set_1[i] == 1 &&
                                      items_set_2[i] == 1 &&
                                      items_set_3[i] == 1;
                if (is_badge) {
                    priority_sum += i + 1;
                    break;
                }
            }

            items_set_1.fill(0);
            items_set_2.fill(0);
            items_set_3.fill(0);
            group_member_count = 0;
        }

        // Fill set for current member
        for (const char ch : line) {
            int prio = GetPriority(ch);
            (*set_list[group_member_count])[prio - 1] = 1;
        }
        // Move index to next member
        ++group_member_count;
    }

    // Duplicate logic to get the last group
    for (int i = 0; i < 52; ++i) {
        const bool is_badge =
            items_set_1[i] == 1 && items_set_2[i] == 1 && items_set_3[i] == 1;
        if (is_badge) {
            priority_sum += i + 1;
            break;
        }
    }

    fmt::print("The sum of priorities is: {}\n", priority_sum);

    return 0;
}