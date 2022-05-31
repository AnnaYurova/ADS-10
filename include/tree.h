// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <string>

class Tree {
 private:
  struct Node {
    char number;
    std::vector<Node*> sheet;
  };
  Node* root;
  std::vector<std::string> substitution;
  void constructTree(Node* root, std::vector<char> newFig) {
    if (!newFig.size()) {
      return;
    }
    if (root->number != '*') {
      for (auto x = newFig.begin(); x != newFig.end(); ++x) {
        if (*x == root->number) {
          newFig.erase(x);
          break;
        }
      }
    }
    for (size_t i = 0; i < newFig.size(); ++i) {
      root->sheet.push_back(new Node);
    }
    for (size_t i = 0; i < root->sheet.size(); ++i) {
      root->sheet[i]->number = newFig[i];
    }
    for (size_t i = 0; i < root->sheet.size(); ++i) {
      constructTree(root->sheet[i], newFig);
    }
  }
  void Permutation(Node*root, std::string s = "") {
    if (!root->sheet.size()) {
      s += root->number;
      substitution.push_back(s);
      return;
    }
    if (root->number != '*') {
      s += root->number;
    }
    for (size_t i = 0; i < root->sheet.size(); ++i) {
      substitution(root->sheet[i], s);
    }
  }

 public:
  explicit Tree(std::vector<char> v) {
    root = new Node;
    root->number = '*';
    constructTree(root, v);
    substitution(root);
  }
  std::string operator[](int i) const {
    if (i >= substitution.size()) {
      return "";
    }
    return substitution[i];
  }
};

#endif  // INCLUDE_TREE_H_
