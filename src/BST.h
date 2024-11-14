//
// Created by Walton Zhang on 2024-11-13.
//

#ifndef ASSIGNMENT_3_SRC_BST_H_
#define ASSIGNMENT_3_SRC_BST_H_
#include <string>
#include <vector>
#include <ostream>

struct Node {
  std::string _data;
  Node* _left {nullptr};
  Node* _right {nullptr};

  Node(std::string data) : _data(data) {}
};

class BST {
  Node* _root {nullptr};

public:
  void insert(const std::string& word);
  void balance();
  bool search(const std::string& word) const;
  void saveToFile(const std::string& filename) const;

  friend std::ostream& operator<<(std::ostream& output, BST& bst);

private:
  Node* insertRecursively(Node* node, const std::string& word);
  void collectInOrder(Node* node, std::vector<std::string>& nodes) const;
  Node* buildBalancedTree(const std::vector<std::string>& nodes, int start, int end);
  bool searchRecursively(Node* node, const std::string& word) const;
  void printTree(Node* node, std::ostream& output, int indent) const;
};

#endif //ASSIGNMENT_3_SRC_BST_H_
