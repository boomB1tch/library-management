#include "Book.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <stdexcept>

Book::Book()
    : bookId(0), title(""), author(""), isbn(""), totalCopies(0), availableCopies(0) {}

Book::Book(int id, const std::string& t, const std::string& a,
           const std::string& i, int copies)
    : bookId(id), title(t), author(a), isbn(i),
      totalCopies(copies), availableCopies(copies) {}

int         Book::getBookId()         const { return bookId; }
std::string Book::getTitle()          const { return title; }
std::string Book::getAuthor()         const { return author; }
std::string Book::getIsbn()           const { return isbn; }
int         Book::getTotalCopies()    const { return totalCopies; }
int         Book::getAvailableCopies()const { return availableCopies; }

bool Book::issueBook() {
    if (availableCopies <= 0) return false;
    --availableCopies;
    return true;
}

bool Book::returnBook() {
    if (availableCopies >= totalCopies) return false;
    ++availableCopies;
    return true;
}

void Book::displayInfo() const {
    std::cout << std::left
              << "  Book ID    : " << bookId          << "\n"
              << "  Title      : " << title           << "\n"
              << "  Author     : " << author          << "\n"
              << "  ISBN       : " << isbn            << "\n"
              << "  Copies     : " << availableCopies
              << " available / " << totalCopies << " total\n";
}

// Format: bookId|title|author|isbn|totalCopies|availableCopies
std::string Book::serialize() const {
    std::ostringstream oss;
    oss << bookId << "|" << title << "|" << author << "|"
        << isbn   << "|" << totalCopies << "|" << availableCopies;
    return oss.str();
}

Book Book::deserialize(const std::string& line) {
    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> parts;
    while (std::getline(iss, token, '|'))
        parts.push_back(token);
    if (parts.size() != 6)
        throw std::runtime_error("Corrupted book record: " + line);

    Book b(std::stoi(parts[0]), parts[1], parts[2], parts[3], std::stoi(parts[4]));
    b.availableCopies = std::stoi(parts[5]);
    return b;
}
