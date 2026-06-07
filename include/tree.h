// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <algorithm>

struct PMNode {
    char value;
    std::vector<PMNode*> children;
    PMNode(char v) : value(v) {}
};

class PMTree {
 private:
    PMNode* root;
    std::vector<char> original;

    void buildFullTree(PMNode* node, std::vector<char> used) {
        std::vector<char> available;
        for (char c : original) {
            if (std::find(used.begin(), used.end(), c) == used.end()) {
                available.push_back(c);
            }
        }
        for (char c : available) {
            PMNode* child = new PMNode(c);
            node->children.push_back(child);
            used.push_back(c);
            buildFullTree(child, used);
            used.pop_back();
        }
    }

    void clearTree(PMNode* node) {
        if (node == nullptr) return;
        for (PMNode* child : node->children) {
            clearTree(child);
        }
        delete node;
    }

 public:
    PMTree(std::vector<char> input) : root(nullptr), original(input) {
        std::sort(original.begin(), original.end());
        root = new PMNode(0);
        std::vector<char> empty;
        buildFullTree(root, empty);
    }

    ~PMTree() {
        clearTree(root);
    }

    PMNode* getRoot() const { return root; }
    std::vector<char> getOriginal() const { return original; }
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
