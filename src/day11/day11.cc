// Copyright 2022 Emmanuel Arias Soto
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.
#include "paths.h"
#include "utils/file_utils.h"

#include <fmt/core.h>
#include <re2/re2.h>
#include <re2/stringpiece.h>

#include <algorithm>
#include <cassert>
#include <optional>
#include <string>
#include <vector>


struct Monkey {
    unsigned int Id;
    std::vector<unsigned int> Items;
    char Op;
    std::optional<unsigned int> OpModifier;
    unsigned int Test;
    unsigned int MonkeyTrue;
    unsigned int MonkeyFalse;
    unsigned int ItemsInspected = 0;

    void DoTurn(std::vector<Monkey>& monkeys)
    {
        for (const auto& item : Items) {
            ++ItemsInspected;
            const unsigned int item_after_op = ApplyOp(item);
            const unsigned int item_bored = item_after_op / 3;
            // fmt::print("{}\n", item_bored);

            if (item_bored % Test == 0) {
                // fmt::print("pass true\n");
                monkeys[MonkeyTrue].Items.push_back(item_bored);
            } else {
                // fmt::print("pass false\n");
                monkeys[MonkeyFalse].Items.push_back(item_bored);
            }
        }
        Items.clear();
    }

   private:
    unsigned int ApplyOp(unsigned int item)
    {
        if (Op == '+') {
            if (OpModifier.has_value()) return item + *OpModifier;
            return item + item;
        }
        if (Op == '*') {
            if (OpModifier.has_value()) return item * *OpModifier;
            return item * item;
        }
        assert(true);
        return 0;
    }
};

struct MonkeyV2 {
    unsigned int Id;
    std::vector<unsigned long long int> Items;
    char Op;
    std::optional<unsigned long long int> OpModifier;
    unsigned int Test;
    unsigned int MonkeyTrue;
    unsigned int MonkeyFalse;
    unsigned long long int ItemsInspected = 0;

    void DoTurn(unsigned long long int magic_num,
                std::vector<MonkeyV2>& monkeys)
    {
        for (const unsigned long long& item : Items) {
            ++ItemsInspected;
            const unsigned long long int item_after_op =
                ApplyOp(item, magic_num);
            // const unsigned int item_bored = item_after_op / 3;
            // fmt::print("{}\n", item_bored);

            if (item_after_op % Test == 0) {
                // fmt::print("pass true\n");
                monkeys[MonkeyTrue].Items.push_back(item_after_op);
            } else {
                // fmt::print("pass false\n");
                monkeys[MonkeyFalse].Items.push_back(item_after_op);
            }
        }
        Items.clear();
    }

   private:
    unsigned long long int ApplyOp(unsigned long long int item,
                                   unsigned long long int magic_num)
    {
        if (Op == '+') {
            unsigned long long int to_sum = item;
            if (OpModifier.has_value()) to_sum = *OpModifier;
            return (item + to_sum) % magic_num;
        }
        if (Op == '*') {
            unsigned long long int to_multiply = item;
            if (OpModifier.has_value()) to_multiply = *OpModifier;
            return (item * to_multiply) % magic_num;
        }
        assert(true);
        return 0;
    }
};

int main()
{
    std::vector<std::string> input = ReadFile(DAY_11_INPUT);
    auto input_it = input.begin();

    unsigned int monkey_id;
    std::vector<MonkeyV2> monkeys;

    while (true) {
        // fmt::print("processing monkey {}\n", monkey_id);

        MonkeyV2& m = monkeys.emplace_back();
        m.Id = monkey_id;

        const std::string& items = *(++input_it);
        re2::StringPiece input_piece(items);
        int value;
        while (re2::RE2::FindAndConsume(&input_piece, "(\\d+)", &value)) {
            m.Items.push_back(value);
        }

        const std::string& operation = *(++input_it);

        char op;
        std::string modifier;
        re2::RE2::FullMatch(operation,
                            "  Operation: new = old (\\+|\\*) (\\w+)", &op,
                            &modifier);
        m.Op = op;
        if (modifier == "old")
            m.OpModifier = std::nullopt;
        else
            m.OpModifier = std::stoll(modifier);

        re2::RE2::PartialMatch(*(++input_it), "(\\d+)", &m.Test);
        re2::RE2::PartialMatch(*(++input_it), "(\\d+)", &m.MonkeyTrue);
        re2::RE2::PartialMatch(*(++input_it), "(\\d+)", &m.MonkeyFalse);
        ++input_it;

        if (input_it == input.end()) break;

        ++monkey_id;
        ++input_it;
    }

    unsigned long long int magic_num = 1;
    for (auto& m : monkeys) magic_num *= m.Test;

    for (int i = 0; i < 10000; ++i) {
        // fmt::print("Round {}\n", i);
        for (auto& m : monkeys) m.DoTurn(magic_num, monkeys);
    }

    std::sort(monkeys.begin(), monkeys.end(),
              [](const MonkeyV2& a, const MonkeyV2& b) {
                  return a.ItemsInspected > b.ItemsInspected;
              });
    fmt::print("{} - {}\n", monkeys[0].ItemsInspected,
               monkeys[1].ItemsInspected);
    fmt::print("{}\n", monkeys[0].ItemsInspected * monkeys[1].ItemsInspected);

    return 0;
}