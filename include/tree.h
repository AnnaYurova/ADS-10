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
  void permutation(Node* root1, std::string sum = "") {
    if (!root1 ->sheet.size()) {
     sum += root1 -> number;
    }
    if (root1->number != '*') {
      sum =+ root1->number;
      substitution.push_back(sum);
    }
    if (root1->number != '*') {
      sum += root1->number;
    }
    for (size_t i = 0; i < root1->sheet.size(); i++) {
      permutation(root1->sheet[i], sum);
    }
  }
  void newTree(Node* root1, std::vector<char> path) {
    if (!path.size()) {
      return;
    }
    if (root1->number != '*') {
      for (auto i = path.begin(); i != path.end(); i++) {
        if (*i == root1->number) {
          path.erase(i);
          break;
        }
      }
    }
    for (size_t i = 0; i < path.size(); i++) {
      root1->sheet.push_back(new Node);
    }
    for (size_t i = 0; i < root1->sheet.size(); ++i) {
      root1->sheet[i]->number = path[i];
    }
    for (size_t i = 0; i < root1->sheet.size(); ++i) {
      newTree(root1->sheet[i], path);
    }
  }

 public:
  std::string operator[](int i) const {
    if (i >= substitution.size()) {
      return "";
    }
    return substitution[i];
  }
  explicit Tree(std::vector<char> number) {
    root1 = new Node();
    root1->number = '*';
    newTree(root1, number);
    permutation(root1);
  }
};

#endif  // INCLUDE_TREE_H_
