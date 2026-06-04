#pragma once
#include <string>

namespace Utils {
    void clearScreen();
    void pauseScreen();
    void printHeader(const std::string& title);
    void printDivider();
    bool isValidName(const std::string& name);
    bool isValidContact(const std::string& contact);
    std::string toLower(const std::string& str);
}
