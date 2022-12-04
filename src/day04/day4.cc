// Copyright 2022 Emmanuel Arias Soto
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.
#include "paths.h"

#include <fmt/core.h>

#include <algorithm>
#include <fstream>
#include <utility>

bool IsOneSectionFullyContained(const std::pair<int, int>& section_1,
                                const std::pair<int, int>& section_2)
{
    int smaller_min = std::min(section_1.first, section_2.first);
    int bigger_max = std::max(section_1.second, section_2.second);

    int union_max = bigger_max - smaller_min;
    int biggest_section = std::max((section_1.second - section_1.first),
                                   (section_2.second - section_2.first));

    return union_max <= biggest_section;
}

int main()
{
    std::ifstream in(DAY_4_INPUT);

    std::pair<int, int> section_1;
    std::pair<int, int> section_2;
    unsigned int fully_contained_sections_count = 0;
    unsigned int overlapped_sections = 0;

    while (!in.eof()) {
        in >> section_1.first;
        in.ignore(1);
        in >> section_1.second;
        in.ignore(1);
        in >> section_2.first;
        in.ignore(1);
        in >> section_2.second;
        in.ignore(1);

        if (IsOneSectionFullyContained(section_1, section_2))
            ++fully_contained_sections_count;

        if (section_1.first > section_2.first) std::swap(section_1, section_2);
        if(section_2.first <= section_1.second) ++overlapped_sections;
    }

    fmt::print(
        "The amount of section pairs that one is fully contained by the other "
        "is : {}\n",
        fully_contained_sections_count);
        fmt::print("The amount of pairs with overlapped sections is: {}\n", overlapped_sections);
    return 0;
}