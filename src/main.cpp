#include <iostream>
#include <fstream>
#include <string>

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

    // Close files
    dictionaryFile.close();
    testFile.close();

    return 0;
}