#include "Member.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

Member::Member()
    : memberId(0), name(""), contact("") {}

Member::Member(int id, const std::string& n, const std::string& c)
    : memberId(id), name(n), contact(c) {}

int         Member::getMemberId()      const { return memberId; }
std::string Member::getName()          const { return name; }
std::string Member::getContact()       const { return contact; }
std::vector<int> Member::getBorrowedBookIds() const { return borrowedBookIds; }
int         Member::getBorrowedCount() const { return (int)borrowedBookIds.size(); }

bool Member::borrowBook(int bookId) {
    if (hasBorrowed(bookId)) return false;
    borrowedBookIds.push_back(bookId);
    return true;
}

bool Member::returnBook(int bookId) {
    auto it = std::find(borrowedBookIds.begin(), borrowedBookIds.end(), bookId);
    if (it == borrowedBookIds.end()) return false;
    borrowedBookIds.erase(it);
    return true;
}

bool Member::hasBorrowed(int bookId) const {
    return std::find(borrowedBookIds.begin(), borrowedBookIds.end(), bookId)
           != borrowedBookIds.end();
}

void Member::displayInfo() const {
    std::cout << std::left
              << "  Member ID  : " << memberId        << "\n"
              << "  Name       : " << name            << "\n"
              << "  Contact    : " << contact         << "\n"
              << "  Borrowed   : " << getBorrowedCount() << " book(s)\n";
}

// Format: memberId|name|contact|bookId1,bookId2,...
std::string Member::serialize() const {
    std::ostringstream oss;
    oss << memberId << "|" << name << "|" << contact << "|";
    for (int i = 0; i < (int)borrowedBookIds.size(); ++i) {
        if (i) oss << ",";
        oss << borrowedBookIds[i];
    }
    return oss.str();
}

Member Member::deserialize(const std::string& line) {
    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> parts;
    while (std::getline(iss, token, '|'))
        parts.push_back(token);
    if (parts.size() != 4)
        throw std::runtime_error("Corrupted member record: " + line);

    Member m(std::stoi(parts[0]), parts[1], parts[2]);
    if (!parts[3].empty()) {
        std::istringstream ids(parts[3]);
        std::string id;
        while (std::getline(ids, id, ','))
            if (!id.empty()) m.borrowedBookIds.push_back(std::stoi(id));
    }
    return m;
}
