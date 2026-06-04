#include "Utils.h"
#include <iostream>
#include <algorithm>
#include <cctype>

namespace Utils {

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    std::cout << "\n  Press Enter to continue...";
    std::cin.ignore(1000, '\n');
    std::cin.get();
}

void printDivider() {
    std::cout << "  " << std::string(52, '=') << "\n";
}

void printHeader(const std::string& title) {
    clearScreen();
    printDivider();
    int padding = (52 - (int)title.size()) / 2;
    if (padding < 0) padding = 0;
    std::cout << "  " << std::string(padding, ' ') << title << "\n";
    printDivider();
    std::cout << "\n";
}

bool isValidName(const std::string& name) {
    if (name.size() < 2) return false;
    return std::all_of(name.begin(), name.end(), [](char c){
        return std::isalpha(c) || c == ' ';
    });
}

bool isValidContact(const std::string& contact) {
    if (contact.size() < 7) return false;
    return std::all_of(contact.begin(), contact.end(), [](char c){
        return std::isdigit(c) || c == '+' || c == '-' || c == ' ';
    });
}

std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

} // namespace Utils
