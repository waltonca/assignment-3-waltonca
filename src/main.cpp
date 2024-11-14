#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype> // for std::isalnum
#include <algorithm>  // for std::transform and std::any_of

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

  bool search(const std::string& word) const {
      return searchRecursively(_root, word);
  }

  // Overloading the << operator prints all words in the tree
  friend std::ostream& operator<<(std::ostream& output, BST& bst) {
      bst.printTree(bst._root, output, 0);
      return output;
  }

  // Save the BST to a file
  void saveToFile(const std::string& filename) const {
      std::ofstream file(filename);
      if (!file.is_open()) {
          std::cerr << "Error: Could not open file " << filename << std::endl;
          return;
      }
      printTree(_root, file, 0);
      file.close();
      std::cout << "Binary Search Tree has been saved to " << filename << std::endl;
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

  bool searchRecursively(Node* node, const std::string& word) const {
      if (node == nullptr) return false;
      if (word == node->_data) return true;
      if (word < node->_data) return searchRecursively(node->_left, word);
      return searchRecursively(node->_right, word);
  }

  void printTree(Node* node, std::ostream& output, int indent) const {
      if (node == nullptr) return;
      printTree(node->_right, output, indent + 2);
      output << std::string(4 * indent, ' ') << node->_data << std::endl;
      printTree(node->_left, output, indent + 2);
  }
};

// Convert a word to lowercase and check if it contains digits
std::string toLowercase(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

bool containsDigits(const std::string& str) {
    return std::any_of(str.begin(), str.end(), ::isdigit);
}

std::vector<std::string> extractWords(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> words;
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return words;
    }

    while (std::getline(file, line)) {
        std::string word;
        for (char ch : line) {
            if (std::isalnum(ch)) {
                word += ch;
            } else if (!word.empty()) {
                word = toLowercase(word);
                if (!containsDigits(word)) {
                    words.push_back(word);
                }
                word.clear();
            }
        }
        if (!word.empty()) {
            word = toLowercase(word);
            if (!containsDigits(word)) {
                words.push_back(word);
            }
        }
    }

    file.close();
    return words;
}

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

    std::cout << "Binary Search Tree (In-Order): \n" << bst << std::endl;

    // Save Binary Search Tree to output file
    bst.saveToFile("../output/bst.txt");

    // Close files
    dictionaryFile.close();

    // Extract words from test file
    std::vector<std::string> testWords = extractWords(argv[2]);
    std::cout << "Misspelled words:" << std::endl;
    for (const auto& testWord : testWords) {
        if (!bst.search(testWord)) {
            std::cout << testWord << std::endl;
        }
    }

    testFile.close();

    return 0;
}