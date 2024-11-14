//
// Created by Walton Zhang on 2024-11-13.
//
#include "application.h"
#include "BST.h"
#include "utility.h"
#include <iostream>
#include <fstream>

bool checkFileOpen(const std::string& filename, const std::string& fileType) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << fileType << " file: " << filename << std::endl;
        return false;
    }
    return true;
}

void runApplication(const std::string& dictionaryFile, const std::string& testFile) {
    BST bst;
    std::ifstream dictFile(dictionaryFile);
    std::string word;

    // Read each word from the dictionary file and insert it into the binary search tree
    while (dictFile >> word) {
        bst.insert(word);
    }

    // balance bst
    bst.balance();

    // Print the Binary Search Tree to the console
    std::cout << "Binary Search Tree (In-Order): \n" << bst << std::endl;

    // Save Binary Search Tree to output file
    bst.saveToFile("../output/bst.txt");
    std::cout << "Saved Binary Search Tree to output/bst.txt" << std::endl;

    // Extract words from test file
    std::vector<std::string> testWords = extractWords(testFile);
    // Print Misspelled words
    std::cout << "Misspelled words:" << std::endl;
    for (const auto& testWord : testWords) {
        if (!bst.search(testWord)) {
            std::cout << testWord << std::endl;
        }
    }
}