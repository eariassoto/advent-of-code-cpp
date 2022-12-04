// Copyright 2022 Emmanuel Arias Soto
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.
#include "paths.h"

#include <fmt/core.h>

#include <algorithm>
#include <fstream>
#include <utility>

int main()
{
    std::ifstream in(DAY_4_INPUT);

    std::pair<int, int> section_1;
    std::pair<int, int> section_2;
    unsigned int fully_contained_sections_count = 0;

    while (!in.eof()) {
        in >> section_1.first;
        in.ignore(1);
        in >> section_1.second;
        in.ignore(1);
        in >> section_2.first;
        in.ignore(1);
        in >> section_2.second;
        in.ignore(1);

        int smaller_min = std::min(section_1.first, section_2.first);
        int bigger_max = std::max(section_1.second, section_2.second);

        int union_max = bigger_max - smaller_min;
        int biggest_section = std::max((section_1.second - section_1.first),
                                       (section_2.second - section_2.first));

        if (union_max <= biggest_section) ++fully_contained_sections_count;
    }

    fmt::print(
        "The amount of section pairs that one is fully contained by the other "
        "is : {}\n",
        fully_contained_sections_count);
    return 0;
}