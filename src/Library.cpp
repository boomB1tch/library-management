#include "Library.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

Library::Library(const std::string& bf, const std::string& mf)
    : booksFile(bf), membersFile(mf), nextBookId(1001), nextMemberId(2001) {
    loadBooks();
    loadMembers();
}

// ── File I/O ───────────────────────────────────────────────────────────────

void Library::loadBooks() {
    std::ifstream f(booksFile);
    if (!f.is_open()) return;
    std::string line;
    while (std::getline(f, line)) {
        if (line.empty()) continue;
        try {
            Book b = Book::deserialize(line);
            books.push_back(b);
            if (b.getBookId() >= nextBookId) nextBookId = b.getBookId() + 1;
        } catch (...) {}
    }
}

void Library::loadMembers() {
    std::ifstream f(membersFile);
    if (!f.is_open()) return;
    std::string line;
    while (std::getline(f, line)) {
        if (line.empty()) continue;
        try {
            Member m = Member::deserialize(line);
            members.push_back(m);
            if (m.getMemberId() >= nextMemberId) nextMemberId = m.getMemberId() + 1;
        } catch (...) {}
    }
}

void Library::saveBooks() const {
    std::ofstream f(booksFile, std::ios::trunc);
    for (const auto& b : books) f << b.serialize() << "\n";
}

void Library::saveMembers() const {
    std::ofstream f(membersFile, std::ios::trunc);
    for (const auto& m : members) f << m.serialize() << "\n";
}

int Library::findBookIndex(int bookId) const {
    for (int i = 0; i < (int)books.size(); ++i)
        if (books[i].getBookId() == bookId) return i;
    return -1;
}

int Library::findMemberIndex(int memberId) const {
    for (int i = 0; i < (int)members.size(); ++i)
        if (members[i].getMemberId() == memberId) return i;
    return -1;
}

bool Library::bookExists(int bookId)     const { return findBookIndex(bookId)     != -1; }
bool Library::memberExists(int memberId) const { return findMemberIndex(memberId) != -1; }

// ── Book Management ────────────────────────────────────────────────────────

int Library::addBook(const std::string& title, const std::string& author,
                     const std::string& isbn, int copies) {
    int id = nextBookId++;
    books.emplace_back(id, title, author, isbn, copies);
    saveBooks();
    return id;
}

bool Library::removeBook(int bookId) {
    int idx = findBookIndex(bookId);
    if (idx == -1) return false;
    books.erase(books.begin() + idx);
    saveBooks();
    return true;
}

// ── Member Management ──────────────────────────────────────────────────────

int Library::addMember(const std::string& name, const std::string& contact) {
    int id = nextMemberId++;
    members.emplace_back(id, name, contact);
    saveMembers();
    return id;
}

bool Library::removeMember(int memberId) {
    int idx = findMemberIndex(memberId);
    if (idx == -1) return false;
    members.erase(members.begin() + idx);
    saveMembers();
    return true;
}

// ── Transactions ───────────────────────────────────────────────────────────

bool Library::issueBook(int memberId, int bookId) {
    int mi = findMemberIndex(memberId);
    int bi = findBookIndex(bookId);
    if (mi == -1 || bi == -1) return false;
    if (!books[bi].issueBook()) return false;
    if (!members[mi].borrowBook(bookId)) { books[bi].returnBook(); return false; }
    saveBooks();
    saveMembers();
    return true;
}

bool Library::returnBook(int memberId, int bookId) {
    int mi = findMemberIndex(memberId);
    int bi = findBookIndex(bookId);
    if (mi == -1 || bi == -1) return false;
    if (!members[mi].returnBook(bookId)) return false;
    books[bi].returnBook();
    saveBooks();
    saveMembers();
    return true;
}

// ── Search ─────────────────────────────────────────────────────────────────

void Library::searchByTitle(const std::string& keyword) const {
    std::string kw = Utils::toLower(keyword);
    bool found = false;
    for (const auto& b : books) {
        if (Utils::toLower(b.getTitle()).find(kw) != std::string::npos) {
            std::cout << "  " << std::string(48, '-') << "\n";
            b.displayInfo();
            found = true;
        }
    }
    if (!found) std::cout << "  [!] No books found with title \"" << keyword << "\".\n";
}

void Library::searchByAuthor(const std::string& keyword) const {
    std::string kw = Utils::toLower(keyword);
    bool found = false;
    for (const auto& b : books) {
        if (Utils::toLower(b.getAuthor()).find(kw) != std::string::npos) {
            std::cout << "  " << std::string(48, '-') << "\n";
            b.displayInfo();
            found = true;
        }
    }
    if (!found) std::cout << "  [!] No books found by author \"" << keyword << "\".\n";
}

// ── Display ────────────────────────────────────────────────────────────────

void Library::displayAllBooks() const {
    if (books.empty()) { std::cout << "  No books in library.\n"; return; }
    std::cout << "  " << std::string(68, '-') << "\n";
    std::cout << "  " << std::left
              << std::setw(8)  << "ID"
              << std::setw(28) << "Title"
              << std::setw(20) << "Author"
              << std::setw(8)  << "Avail" << "\n";
    std::cout << "  " << std::string(68, '-') << "\n";
    for (const auto& b : books) {
        std::cout << "  " << std::left
                  << std::setw(8)  << b.getBookId()
                  << std::setw(28) << b.getTitle().substr(0, 26)
                  << std::setw(20) << b.getAuthor().substr(0, 18)
                  << b.getAvailableCopies() << "/" << b.getTotalCopies() << "\n";
    }
    std::cout << "  " << std::string(68, '-') << "\n";
}

void Library::displayAllMembers() const {
    if (members.empty()) { std::cout << "  No members registered.\n"; return; }
    std::cout << "  " << std::string(56, '-') << "\n";
    std::cout << "  " << std::left
              << std::setw(10) << "ID"
              << std::setw(24) << "Name"
              << std::setw(16) << "Contact"
              << std::setw(8)  << "Borrowed" << "\n";
    std::cout << "  " << std::string(56, '-') << "\n";
    for (const auto& m : members) {
        std::cout << "  " << std::left
                  << std::setw(10) << m.getMemberId()
                  << std::setw(24) << m.getName().substr(0, 22)
                  << std::setw(16) << m.getContact().substr(0, 14)
                  << m.getBorrowedCount() << "\n";
    }
    std::cout << "  " << std::string(56, '-') << "\n";
}

void Library::displayBook(int bookId) const {
    int idx = findBookIndex(bookId);
    if (idx == -1) { std::cout << "  [!] Book not found.\n"; return; }
    books[idx].displayInfo();
}

void Library::displayMember(int memberId) const {
    int idx = findMemberIndex(memberId);
    if (idx == -1) { std::cout << "  [!] Member not found.\n"; return; }
    members[idx].displayInfo();
}

void Library::displayBorrowedBooks(int memberId) const {
    int idx = findMemberIndex(memberId);
    if (idx == -1) { std::cout << "  [!] Member not found.\n"; return; }
    auto ids = members[idx].getBorrowedBookIds();
    if (ids.empty()) { std::cout << "  No books currently borrowed.\n"; return; }
    for (int id : ids) displayBook(id);
}
