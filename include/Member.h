#pragma once
#include <string>
#include <vector>

class Member {
private:
    int memberId;
    std::string name;
    std::string contact;
    std::vector<int> borrowedBookIds;

public:
    Member();
    Member(int id, const std::string& name, const std::string& contact);

    int getMemberId() const;
    std::string getName() const;
    std::string getContact() const;
    std::vector<int> getBorrowedBookIds() const;
    int getBorrowedCount() const;

    bool borrowBook(int bookId);
    bool returnBook(int bookId);
    bool hasBorrowed(int bookId) const;

    void displayInfo() const;
    std::string serialize() const;
    static Member deserialize(const std::string& line);
};
