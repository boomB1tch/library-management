#pragma once
#include "Book.h"
#include "Member.h"
#include <vector>
#include <string>

class Library {
private:
    std::vector<Book> books;
    std::vector<Member> members;
    std::string booksFile;
    std::string membersFile;
    int nextBookId;
    int nextMemberId;

    void loadBooks();
    void loadMembers();
    void saveBooks() const;
    void saveMembers() const;
    int findBookIndex(int bookId) const;
    int findMemberIndex(int memberId) const;

public:
    Library(const std::string& booksFile  = "data/books.dat",
            const std::string& membersFile = "data/members.dat");

    // Book management
    int  addBook(const std::string& title, const std::string& author,
                 const std::string& isbn, int copies);
    bool removeBook(int bookId);

    // Member management
    int  addMember(const std::string& name, const std::string& contact);
    bool removeMember(int memberId);

    // Transactions
    bool issueBook(int memberId, int bookId);
    bool returnBook(int memberId, int bookId);

    // Search
    void searchByTitle(const std::string& keyword) const;
    void searchByAuthor(const std::string& keyword) const;

    // Display
    void displayAllBooks() const;
    void displayAllMembers() const;
    void displayBook(int bookId) const;
    void displayMember(int memberId) const;
    void displayBorrowedBooks(int memberId) const;

    bool bookExists(int bookId) const;
    bool memberExists(int memberId) const;
};
