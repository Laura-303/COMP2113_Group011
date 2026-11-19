#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>

inline void printHeader(const std::string& title) {
    std::cout << "\n========================================\n";
    std::cout << "  " << title << "\n";
    std::cout << "========================================\n";
}

#endif
