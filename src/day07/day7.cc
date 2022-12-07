// Copyright 2022 Emmanuel Arias Soto
// Use of this source code is governed by a MIT license that can be
// found in the LICENSE file.
#include "paths.h"
#include "utils/file_utils.h"

#include <fmt/core.h>

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <utility>
#include <queue>

class Node
{
   public:
    Node(const std::string& name) : name_(name), isFile_(false) {}

    Node* GetParent() const
    {
        assert(!isFile_);
        return parent_;
    };

    Node* GetChild(const std::string& name) const
    {
        assert(!isFile_);
        auto it = std::find_if(children_.begin(), children_.end(),
                               [&name](const Node* node) {
                                   return !node->isFile_ && node->name_ == name;
                               });
        if (it != children_.end()) return *it;
        return nullptr;
    };

    void AddFile(const std::string& name, unsigned int size)
    {
        Node* f = new Node();
        f->name_ = name;
        f->size_ = size;
        f->isFile_ = true;
        f->parent_ = this;
        children_.push_back(f);
    }

    void AddDirectory(const std::string& name)
    {
        Node* f = new Node();
        f->name_ = name;
        f->isFile_ = false;
        f->parent_ = this;
        children_.push_back(f);
    }

    unsigned int GetSumAllUnder100k()
    {
        unsigned int result = 0;
        GetSumAux(&result);
        return result;
    }
    unsigned int GetTotalSum()
    {
        unsigned int result = 0;
        return GetSumAux(&result);
    }
    unsigned int FindDirSizeToDelete(unsigned int free_space)
    {
        unsigned int result = std::numeric_limits<unsigned int>::max();
        FindDirSizeToDeleteAux(free_space, &result);
        return result;
    }

    static void DeleteNode(const Node* node)
    {
        std::queue<const Node*> to_delete;
        to_delete.emplace(node);
        while (!to_delete.empty()) {
            for (const Node* n : to_delete.front()->children_) {
                to_delete.emplace(n);
            }
            to_delete.pop();
        }
    }

   private:
    Node() = default;

    unsigned int GetSumAux(unsigned int* sum)
    {
        // fmt::print("GetSumAux {}, sum: {}\n", name_, *sum);
        unsigned int res = 0;
        for (int i = 0; i < children_.size(); ++i) {
            if (children_[i]->isFile_)
                res += children_[i]->size_;
            else
                res += children_[i]->GetSumAux(sum);
        }
        if (res <= 100000) *sum += res;
        // fmt::print("GetSumAux {}, sum is now: {}\n", name_, *sum);
        // fmt::print("GetSumAux {}, res is now: {}\n", name_, res);
        return res;
    }

    unsigned int FindDirSizeToDeleteAux(unsigned int free_space,
                                        unsigned int* result)
    {
        unsigned int res = 0;
        for (int i = 0; i < children_.size(); ++i) {
            if (children_[i]->isFile_)
                res += children_[i]->size_;
            else
                res += children_[i]->FindDirSizeToDeleteAux(free_space, result);
        }
        if (free_space + res >= 30000000) {
            *result = std::min(*result, free_space + res);
        }
        return res;
    }

    std::string name_;
    bool isFile_ = false;
    unsigned int size_ = 0;

    Node* parent_ = nullptr;
    std::vector<Node*> children_;
};

using InputIt = std::vector<std::string>::iterator;

void FillDirectory(Node* dir, InputIt& curr_command, const InputIt& command_end)
{
    ++curr_command;
    while (curr_command != command_end && (*curr_command)[0] != '$') {
        auto pos = (*curr_command).find(' ');
        auto first_half = (*curr_command).substr(0, pos);
        auto second_half = (*curr_command).substr(pos + 1);
        if (first_half == "dir") {
            // fmt::print("adding dir {}\n", second_half);
            dir->AddDirectory(second_half);
        } else {
            // fmt::print("adding file {} size {}\n", second_half, first_half);
            dir->AddFile(second_half, stoi(first_half));
        }
        ++curr_command;
    }
}

int main()
{
    std::vector<std::string> input = ReadFile(DAY_7_INPUT);

    Node* root = new Node("/");
    Node* aux = root;
    InputIt curr_command = input.begin() + 1;

    while (curr_command != input.end()) {
        if ((*curr_command) == "$ ls") {
            // fmt::print("found ls\n");
            FillDirectory(aux, curr_command, input.end());
        } else {
            auto dir = (*curr_command).substr(5);
            if (dir == "..") {
                // fmt::print("cd to parent\n");
                aux = aux->GetParent();
            } else {
                // fmt::print("cd to: {}\n", dir);
                aux = aux->GetChild(dir);
            }
            ++curr_command;
        }
    }

    unsigned int sum = root->GetSumAllUnder100k();
    fmt::print("size sum of directories under 100k: {}\n", sum);

    unsigned int total = root->GetTotalSum();
    fmt::print("total sum: {}\n", total);

    unsigned int free_space = 70000000 - total;
    fmt::print("free space: {}\n", free_space);

    Node::DeleteNode(root);
    unsigned int size_to_delete = root->FindDirSizeToDelete(free_space);
    fmt::print("dir size to delete: {}\n", size_to_delete - free_space);

    return 0;
}