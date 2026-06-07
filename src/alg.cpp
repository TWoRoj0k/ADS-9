// Copyright 2022 NNTU-CS
#include <vector>
#include "tree.h"

static void getAllPathsHelper(PMNode* node, std::vector<char>& current,
                              std::vector<std::vector<char>>& result) {
    if (!node) return;
    if (node->value != 0) {
        current.push_back(node->value);
    }
    if (node->children.empty()) {
        if (!current.empty()) {
            result.push_back(current);
        }
    } else {
        for (PMNode* child : node->children) {
            getAllPathsHelper(child, current, result);
        }
    }
    if (node->value != 0) {
        current.pop_back();
    }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    getAllPathsHelper(tree.getRoot(), current, result);
    return result;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    std::vector<std::vector<char>> all = getAllPerms(tree);
    if (num < 1 || num > static_cast<int>(all.size())) {
        return std::vector<char>();
    }
    return all[num - 1];
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    std::vector<char> orig = tree.getOriginal();
    int n = orig.size();
    int total = 1;
    for (int i = 2; i <= n; i++) total *= i;
    if (num < 1 || num > total) return std::vector<char>();
    num--;
    std::vector<char> available = orig;
    std::vector<char> result;
    int fact = total / n;
    for (int i = n; i > 0; i--) {
        int index = num / fact;
        result.push_back(available[index]);
        available.erase(available.begin() + index);
        num %= fact;
        if (i > 1) fact /= (i - 1);
    }
    return result;
}
