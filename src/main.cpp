#include "application.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <dictionary_file> <test_file>" << std::endl;
        return 1;
    }

    // use checkFileOpen check file
    if (!checkFileOpen(argv[1], "dictionary") || !checkFileOpen(argv[2], "test")) {
        return 1;
    }

    std::cout << "Files loaded successfully!" << std::endl;

    runApplication(argv[1], argv[2]);
    return 0;
}