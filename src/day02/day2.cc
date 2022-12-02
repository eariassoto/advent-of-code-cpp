// Copyright 2022 Emmanuel Arias Soto
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.
#include "paths.h"

#include <fmt/core.h>

#include <cassert>
#include <fstream>

// assume 0 = rock, 1 = paper, 2 = scissors
unsigned int GetPlayScore(unsigned int opponent_move, unsigned int own_move)
{
    if (opponent_move == own_move) {  // draw
        return 3;
    }
    if (opponent_move == 0) {  // rock
        if (own_move == 1)     // paper
            return 6;
        // scissors
        return 0;
    }
    if (opponent_move == 1) {  // paper
        if (own_move == 2)     // scissors
            return 6;
        // rock
        return 0;
    }
    if (opponent_move == 2) {  // scissors
        if (own_move == 0)     // rock
            return 6;
        // paper
        return 0;
    }
    assert(true);
    return 0;
}

// assume move 0 = rock, 1 = paper, 2 = scissors
// assume hint 0 = lose, 1 = draw, 2 = win
unsigned int GetMovewithHint(unsigned int opponent_move, unsigned int hint)
{
    if (hint == 1) {  // draw
        return opponent_move;
    }
    if (opponent_move == 0) {  // rock
        if (hint == 0)         // lose
            return 2;          // scissors
        // win
        return 1;  // paper
    }
    if (opponent_move == 1) {  // paper
        if (hint == 0)         // lose
            return 0;          // rock
        // win
        return 2;  // scissors
    }
    if (opponent_move == 2) {  // scissors
        if (hint == 0)         // lose
            return 1;          // paper
        // win
        return 0;  // rock
    }
    assert(true);
    return 0;
}

int main()
{
    std::ifstream in(DAY_2_INPUT);

    char opponent_input;
    char own_input;
    unsigned int original_total_score = 0;
    unsigned int hinted_total_score = 0;

    while (!in.eof()) {
        in >> opponent_input >> own_input;
        in.ignore(1);

        unsigned int opponent_move = opponent_input - 'A';
        unsigned int original_own_move = own_input - 'X';
        unsigned int hinted_own_move =
            GetMovewithHint(opponent_move, original_own_move);

        original_total_score += original_own_move + 1;
        original_total_score += GetPlayScore(opponent_move, original_own_move);

        hinted_total_score += hinted_own_move + 1;
        hinted_total_score += GetPlayScore(opponent_move, hinted_own_move);
    }

    fmt::print("The initial total score expected is: {}\n",
               original_total_score);
    fmt::print("The total score after hints is: {}\n", hinted_total_score);
    return 0;
}