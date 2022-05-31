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
  Node* root1;
  std::vector<std::string> substitution;
  void constructTree(Node* root1, std::vector<char> newFig) {
    if (!newFig.size()) {
      return;
    }
    if (root1->number != '*') {
      for (auto x = newFig.begin(); x != newFig.end(); ++x) {
        if (*x == root1->number) {
          newFig.erase(x);
          break;
        }
      }
    }
    for (size_t i = 0; i < newFig.size(); ++i) {
      root1->sheet.push_back(new Node);
    }
    for (size_t i = 0; i < root1->sheet.size(); ++i) {
      root1->sheet[i]->number = newFig[i];
    }
    for (size_t i = 0; i < root1->sheet.size(); ++i) {
      constructTree(root1->sheet[i], newFig);
    }
  }
  void substitution(Node*root1, std::string s = "") {
    if (!root1->sheet.size()) {
      s += root1->number;
      substitution.push_back(s);
      return;
    }
    if (root1->number != '*') {
      s += root1->number;
    }
    for (size_t i = 0; i < root1->sheet.size(); ++i) {
      substitution(root1->sheet[i], s);
    }
  }

 public:
  explicit Tree(std::vector<char> v) {
    root1 = new Node;
    root1->number = '*';
    constructTree(root1, v);
    substitution(root1);
  }
  std::string operator[](int i) const {
    if (i >= substitution.size()) {
      return "";
    }
    return substitution[i];
  }
};

#endif  // INCLUDE_TREE_H_
