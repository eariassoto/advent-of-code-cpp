// Copyright 2022 Emmanuel Arias Soto
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.
#include "paths.h"
#include "utils/file_utils.h"

#include <fmt/core.h>

#include <fstream>
#include <algorithm>

int main()
{
    std::ifstream in(DAY_1_INPUT);

    unsigned int top1_cal_sum = 0;
    unsigned int top2_cal_sum = 0;
    unsigned int top3_cal_sum = 0;
    while (!in.eof()) {
        unsigned int curr_cal_sum = 0;
        while (!std::isspace(in.peek()) && !in.eof()) {
            unsigned int read_calorie;
            in >> read_calorie;
            curr_cal_sum += read_calorie;
            in.ignore(1);
        }
        if (curr_cal_sum >= top1_cal_sum) {
            std::swap(top2_cal_sum, top3_cal_sum);
            std::swap(top1_cal_sum, top2_cal_sum);
            top1_cal_sum = curr_cal_sum;
        } else if (curr_cal_sum >= top2_cal_sum) {
            std::swap(top2_cal_sum, top3_cal_sum);
            top2_cal_sum = curr_cal_sum;
        } else if (curr_cal_sum >= top3_cal_sum) {
            top3_cal_sum = curr_cal_sum;
        }
        in.ignore(1);
    }

    fmt::print("Highest calories count is: {}\n", top1_cal_sum);
    fmt::print("The sum of the three highest calories counts is: {}\n",
               (top1_cal_sum + top2_cal_sum + top3_cal_sum));
    return 0;
}