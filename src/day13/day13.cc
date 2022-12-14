// Copyright 2022 Emmanuel Arias Soto
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.
#include "paths.h"
#include "utils/file_utils.h"

#include <fmt/core.h>

#include <algorithm>
#include <cassert>
#include <optional>
#include <string>
#include <vector>

struct List {
    bool IsInteger;
    std::vector<List> Items;
    List* Parent;

    unsigned int Value;

    bool HasIndex(unsigned int index) { return index < Items.size(); }

    void ConvertToList()
    {
        IsInteger = false;
        List& new_int = Items.emplace_back();
        new_int.IsInteger = true;
        new_int.Parent = this;
        new_int.Value = Value;
    }
};

List* CreateList(const std::string list_str)
{
    bool done = false;
    List* root = new List();
    root->Parent = nullptr;

    List* curr_list = root;
    for (int i = 1; i < list_str.size();) {
        assert(!done);
        char curr_char = list_str[i];
        if (std::isdigit(curr_char)) {
            std::size_t pos;
            const unsigned int number = std::stoi(list_str.substr(i), &pos);
            // fmt::print("process number {}\n", number);
            List& new_int = curr_list->Items.emplace_back();
            new_int.IsInteger = true;
            new_int.Parent = curr_list;
            new_int.Value = number;
            i += pos;

            if (list_str[i] == ',') {
                ++i;  // Consume ,
            }
            continue;
        }
        if (curr_char == '[') {
            // push new list
            List& new_list = curr_list->Items.emplace_back();
            new_list.IsInteger = false;
            new_list.Parent = curr_list;
            curr_list = &new_list;
            ++i;  //  consume [
            continue;
        }
        if (curr_char == ']') {
            if (curr_list->Parent == nullptr) {
                done = true;

            } else {
                curr_list = curr_list->Parent;
            }
            ++i;

            if (list_str[i] == ',') {
                ++i;  // Consume ,
            }
            continue;
        }
        assert(true);
    }
    return root;
}

std::optional<bool> CompareLists(List* left, List* right)
{
    int curr_index = 0;
    while (true) {
        const bool has_left = left->HasIndex(curr_index);
        const bool has_right = right->HasIndex(curr_index);
        if (!has_left && !has_right) return std::nullopt;  // cannot tell

        if (!has_left) {
            return true;  // they are ordered}
        }
        if (!has_right) {
            return false;
        }

        // both have items, compare
        const bool is_left_int = left->Items[curr_index].IsInteger;
        const bool is_right_int = right->Items[curr_index].IsInteger;

        if (is_left_int && is_right_int) {
            if (left->Items[curr_index].Value < right->Items[curr_index].Value)
                return true;
            if (left->Items[curr_index].Value > right->Items[curr_index].Value)
                return false;
            ++curr_index;
            continue;
        }

        if (is_left_int) {
            left->Items[curr_index].ConvertToList();
        }
        if (is_right_int) {
            right->Items[curr_index].ConvertToList();
        }
        auto value =
            CompareLists(&left->Items[curr_index], &right->Items[curr_index]);
        if (value.has_value()) return *value;
        ++curr_index;
    }
    return false;
}

bool Compare(List* left, List* right)
{
    auto val = CompareLists(left, right);
    assert(val.has_value());
    return *val;
}

int main()
{
    std::vector<std::string> input = ReadFile(DAY_13_INPUT);
    // for (const std::string& line : input) fmt::print("{}\n", line);

    // unsigned int res = 0;
    // for (int i = 0; i < input.size(); i += 3) {
    //     // fmt::print("l: {}\n", input[i]);
    //     // fmt::print("r: {}\n", input[i + 1]);
    //     List* l_list = CreateList(input[i]);
    //     List* r_list = CreateList(input[i + 1]);

    //     auto value = CompareLists(l_list, r_list);
    //     assert(value.has_value());
    //     fmt::print("pair {}: {}\n", (i / 3) + 1, *value);
    //     if (*value) res += (i / 3) + 1;
    //     // fmt::print("compare: {}\n", *CompareLists(l_list, r_list));

    //     delete l_list;
    //     delete r_list;
    // }
    // fmt::print("res: {}\n", res);

    std::vector<List*> packets;
    for (const std::string& line : input) {
        packets.push_back(CreateList(line));
    }
    List* pack_2 = packets[packets.size() - 2];
    List* pack_6 = packets[packets.size() - 1];

    std::sort(packets.begin(), packets.end(), &Compare);

    const auto it_2 = std::find(packets.begin(), packets.end(), pack_2);
    const auto it_6 = std::find(packets.begin(), packets.end(), pack_6);

    const unsigned int index_2 = it_2 - packets.begin() + 1;
    const unsigned int index_6 = it_6 - packets.begin() + 1;
    fmt::print("res: {}\n", index_6 * index_2);

    for (const auto& p : packets) {
        delete p;
    }
    return 0;
}