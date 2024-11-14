//
// Created by Walton Zhang on 2024-11-13.
//
#include "utility.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>

// Convert a word to lowercase and check if it contains digits
std::string toLowercase(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

bool containsDigits(const std::string& str) {
    return std::any_of(str.begin(), str.end(), ::isdigit);
}

// Extract words from test file
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