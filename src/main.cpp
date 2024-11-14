#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Node {
  std::string _data;  // save words
  Node* _left {nullptr};
  Node* _right {nullptr};

  Node(std::string data) : _data(data) {}
};

class BST {
  Node* _root {nullptr};

public:
  void insert(const std::string& word) {
      _root = insertRecursively(_root, word);
  }

  void balance() {
      std::vector<std::string> nodes;
      collectInOrder(_root, nodes);  // 收集节点数据
      _root = buildBalancedTree(nodes, 0, nodes.size() - 1);  // 构建平衡树
  }

  // Overloading the << operator prints all words in the tree
  friend std::ostream& operator<<(std::ostream& output, BST& bst) {
      bst.printTree(bst._root, output, 0);
      return output;
  }

private:
  // Recursive insertion of strings
  Node* insertRecursively(Node* node, const std::string& word) {
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

  void collectInOrder(Node* node, std::vector<std::string>& nodes) const {
      if (node == nullptr) return;
      collectInOrder(node->_left, nodes);
      nodes.push_back(node->_data);
      collectInOrder(node->_right, nodes);
  }

  Node* buildBalancedTree(const std::vector<std::string>& nodes, int start, int end) {
      if (start > end) return nullptr;
      int mid = (start + end) / 2;
      Node* root = new Node(nodes[mid]);
      root->_left = buildBalancedTree(nodes, start, mid - 1);
      root->_right = buildBalancedTree(nodes, mid + 1, end);
      return root;
  }

  void printTree(Node* node, std::ostream& output, int indent) const {
      if (node == nullptr) return;

      printTree(node->_right, output, indent + 1);

      output << std::string(4 * indent, ' ') << node->_data << std::endl;

      printTree(node->_left, output, indent + 1);
  }
};

int main(int argc, char* argv[]) {
    // Check if two arguments are provided
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <dictionary_file> <test_file>" << std::endl;
        return 1;
    }

    // Check whether dictionaryFile can open
    std::ifstream dictionaryFile(argv[1]);
    if (!dictionaryFile.is_open()) {
        std::cerr << "Error: Could not open dictionary file: " << argv[1] << std::endl;
        return 1;
    }

    // Check whether testFile can open
    std::ifstream testFile(argv[2]);
    if (!testFile.is_open()) {
        std::cerr << "Error: Could not open test file: " << argv[2] << std::endl;
        return 1;
    }

    // Print success message
    std::cout << "Files loaded successfully!" << std::endl;

    // Some operations
    BST bst;
    std::string word;

    // Read each word from the dictionary file and insert it into the binary search tree
    while (dictionaryFile >> word) {
        bst.insert(word);
    }

    // balance bst
    bst.balance();

    std::cout << "Binary Search Tree (In-Order): " << bst << std::endl;

    // Close files
    dictionaryFile.close();
    testFile.close();

    return 0;
}