// Copyright 2022 Emmanuel Arias Soto
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.
#include "paths.h"

#include <fmt/core.h>

#include <fstream>
#include <unordered_map>
#include <utility>
#include <string>

struct Node {
    Node(char l) : Label(l) {}

    char Label;
    Node* Next = nullptr;
};

void DeleteNodeList(Node* n)
{
    Node* head = n;
    Node* aux = nullptr;
    while (head != nullptr) {
        aux = head->Next;
        delete head;
        head = aux;
    }
}

int main()
{
    std::ifstream in(DAY_5_INPUT);
    if (!in) return 1;

    int crate_count = 0;
    // this logic assumes single digit stack counts
    std::string line;
    const unsigned int stack_stride = 4;
    while (true) {
        std::getline(in, line);
        if (std::isdigit(line[1])) {
            // fmt::print(".{}. {}", line, line.size());
            crate_count = (line.size() + 1) / stack_stride;
            break;
        }
    }
    in.seekg(0);

    // key: crate index
    // value: head and tail
    std::unordered_map<int, std::pair<Node*, Node*>> crates;

    while (true) {
        std::getline(in, line);
        if (std::isdigit(line[1])) {
            break;
        }

        for (unsigned int i = 0; i < crate_count; ++i) {
            const unsigned int crate_label_idx = 1 + (stack_stride * i);
            if (line[crate_label_idx] == ' ') continue;

            auto it = crates.find(i);
            if (it == crates.end()) {
                auto new_node = new Node(line[crate_label_idx]);
                crates.emplace(i, std::make_pair(new_node, new_node));
            } else {
                // Create new, append to tail, update new tail
                auto new_crate = new Node(line[crate_label_idx]);
                it->second.second->Next = new_crate;
                it->second.second = new_crate;
            }
        }
    }

    // for (const auto& [k, v] : crates) {
    //     fmt::print("Stack #{}:\n", k);
    //     Node* head = v.first;
    //     Node* aux = nullptr;
    //     while (head != nullptr) {
    //         aux = head->Next;
    //         fmt::print(" [{}] ", head->Label);
    //         head = aux;
    //     }
    //     fmt::print("\n");
    // }

    // Ignore first whileline
    std::getline(in, line);

    std::string aux;
    while (!in.eof()) {
        // ignore " move "
        in >> aux;
        unsigned int repeat = 0;
        in >> repeat;

        // ignore " from "
        in >> aux;
        unsigned int stack_from = 0;
        in >> stack_from;

        // ignore " to "
        in >> aux;
        unsigned int stack_to = 0;
        in >> stack_to;

        for (unsigned int i = 0; i < repeat; ++i) {
            Node* crate_to_move = crates[stack_from - 1].first;
            crates[stack_from - 1].first = crate_to_move->Next;

            crate_to_move->Next = crates[stack_to - 1].first;
            crates[stack_to - 1].first = crate_to_move;
        }

        // fmt::print("move {} from {} to {}\n", repeat, stack_from, stack_to);
        in.ignore(1);
    }

    // for (const auto& [k, v] : crates) {
    //     fmt::print("Stack #{}:\n", k);
    //     Node* head = v.first;
    //     Node* aux = nullptr;
    //     while (head != nullptr) {
    //         aux = head->Next;
    //         fmt::print(" [{}] ", head->Label);
    //         head = aux;
    //     }
    //     fmt::print("\n");
    // }

    for (unsigned int i = 0; i < crate_count; ++i) {
        fmt::print("{}", crates[i].first->Label);
    }
    fmt::print("\n");

    for (const auto& [k, v] : crates) {
        DeleteNodeList(v.first);
    }
    return 0;
}