#pragma once
#include <string>

class Book {
private:
int bookId;
std::string title;
std::string author;
std::string isbn;
int totalCopies;
int availableCopies;

public:
Book();
Book(int id, const std::string& title, const std::string& author,
const std::string& isbn, int copies);

int getBookId() const;
std::string getTitle() const;
std::string getAuthor() const;
std::string getIsbn() const;
int getTotalCopies() const;
int getAvailableCopies() const;

bool issueBook();
bool returnBook();

void displayInfo() const;
std::string serialize() const;
static Book deserialize(const std::string& line);
};
