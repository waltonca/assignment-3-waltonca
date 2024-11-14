//
// Created by Walton Zhang on 2024-11-13.
//
#include "BST.h"
#include <fstream>
#include <iostream>

void BST::insert(const std::string& word) {
    _root = insertRecursively(_root, word);
}

void BST::balance() {
    std::vector<std::string> nodes;
    collectInOrder(_root, nodes);
    _root = buildBalancedTree(nodes, 0, nodes.size() - 1);
}

bool BST::search(const std::string& word) const {
    return searchRecursively(_root, word);
}

void BST::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }
    printTree(_root, file, 0);
    file.close();
}

Node* BST::insertRecursively(Node* node, const std::string& word) {
    if (node == nullptr) {
        return new Node(word);
    }
    if (word < node->_data) {
        node->_left = insertRecursively(node->_left, word);
    } else if (word > node->_data) {
        node->_right = insertRecursively(node->_right, word);
    }
    return node;
}

void BST::collectInOrder(Node* node, std::vector<std::string>& nodes) const {
    if (node == nullptr) return;
    collectInOrder(node->_left, nodes);
    nodes.push_back(node->_data);
    collectInOrder(node->_right, nodes);
}

Node* BST::buildBalancedTree(const std::vector<std::string>& nodes, int start, int end) {
    if (start > end) return nullptr;
    int mid = (start + end) / 2;
    Node* root = new Node(nodes[mid]);
    root->_left = buildBalancedTree(nodes, start, mid - 1);
    root->_right = buildBalancedTree(nodes, mid + 1, end);
    return root;
}

bool BST::searchRecursively(Node* node, const std::string& word) const {
    if (node == nullptr) return false;
    if (word == node->_data) return true;
    if (word < node->_data) return searchRecursively(node->_left, word);
    return searchRecursively(node->_right, word);
}

void BST::printTree(Node* node, std::ostream& output, int indent) const {
    if (node == nullptr) return;
    printTree(node->_right, output, indent + 2);
    output << std::string(4 * indent, ' ') << node->_data << std::endl;
    printTree(node->_left, output, indent + 2);
}
std::ostream& operator<<(std::ostream& output, BST& bst) {
    bst.printTree(bst._root, output, 0);  // 打印树的方法
    return output;
}