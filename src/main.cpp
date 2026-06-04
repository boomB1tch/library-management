#include "Library.h"
#include "Utils.h"
#include <iostream>
#include <limits>
#include <string>

static int readInt(const std::string& prompt) {
    int val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) { std::cin.ignore(); return val; }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  [!] Invalid input. Try again.\n";
    }
}

static std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

// ── Book Menus ─────────────────────────────────────────────────────────────

void addBookMenu(Library& lib) {
    Utils::printHeader("ADD BOOK");
    std::string title  = readLine("  Title   : ");
    std::string author = readLine("  Author  : ");
    std::string isbn   = readLine("  ISBN    : ");
    int copies         = readInt ("  Copies  : ");
    if (copies <= 0) { std::cout << "  [!] Copies must be positive.\n"; Utils::pauseScreen(); return; }
    int id = lib.addBook(title, author, isbn, copies);
    std::cout << "  [✓] Book added. ID: " << id << "\n";
    Utils::pauseScreen();
}

void removeBookMenu(Library& lib) {
    Utils::printHeader("REMOVE BOOK");
    int id = readInt("  Book ID : ");
    if (lib.removeBook(id))
        std::cout << "  [✓] Book removed.\n";
    else
        std::cout << "  [!] Book not found.\n";
    Utils::pauseScreen();
}

void viewBooksMenu(Library& lib) {
    Utils::printHeader("ALL BOOKS");
    lib.displayAllBooks();
    Utils::pauseScreen();
}

void viewBookMenu(Library& lib) {
    Utils::printHeader("BOOK DETAILS");
    int id = readInt("  Book ID : ");
    lib.displayBook(id);
    Utils::pauseScreen();
}

// ── Member Menus ───────────────────────────────────────────────────────────

void addMemberMenu(Library& lib) {
    Utils::printHeader("ADD MEMBER");
    std::string name    = readLine("  Name    : ");
    if (!Utils::isValidName(name)) {
        std::cout << "  [!] Invalid name.\n"; Utils::pauseScreen(); return;
    }
    std::string contact = readLine("  Contact : ");
    int id = lib.addMember(name, contact);
    std::cout << "  [✓] Member added. ID: " << id << "\n";
    Utils::pauseScreen();
}

void removeMemberMenu(Library& lib) {
    Utils::printHeader("REMOVE MEMBER");
    int id = readInt("  Member ID : ");
    if (lib.removeMember(id))
        std::cout << "  [✓] Member removed.\n";
    else
        std::cout << "  [!] Member not found.\n";
    Utils::pauseScreen();
}

void viewMembersMenu(Library& lib) {
    Utils::printHeader("ALL MEMBERS");
    lib.displayAllMembers();
    Utils::pauseScreen();
}

void viewMemberMenu(Library& lib) {
    Utils::printHeader("MEMBER DETAILS");
    int id = readInt("  Member ID : ");
    lib.displayMember(id);
    Utils::pauseScreen();
}

// ── Transaction Menus ──────────────────────────────────────────────────────

void issueBookMenu(Library& lib) {
    Utils::printHeader("ISSUE BOOK");
    int memberId = readInt("  Member ID : ");
    int bookId   = readInt("  Book ID   : ");
    if (lib.issueBook(memberId, bookId))
        std::cout << "  [✓] Book issued successfully.\n";
    else
        std::cout << "  [!] Failed. Check IDs, availability, or duplicate issue.\n";
    Utils::pauseScreen();
}

void returnBookMenu(Library& lib) {
    Utils::printHeader("RETURN BOOK");
    int memberId = readInt("  Member ID : ");
    int bookId   = readInt("  Book ID   : ");
    if (lib.returnBook(memberId, bookId))
        std::cout << "  [✓] Book returned successfully.\n";
    else
        std::cout << "  [!] Failed. Check IDs or borrowing record.\n";
    Utils::pauseScreen();
}

void viewBorrowedMenu(Library& lib) {
    Utils::printHeader("BORROWED BOOKS");
    int id = readInt("  Member ID : ");
    lib.displayBorrowedBooks(id);
    Utils::pauseScreen();
}

// ── Search Menus ───────────────────────────────────────────────────────────

void searchMenu(Library& lib) {
    Utils::printHeader("SEARCH BOOKS");
    std::cout << "  [1]  Search by Title\n"
              << "  [2]  Search by Author\n\n";
    int choice = readInt("  Enter choice : ");
    if (choice == 1) {
        std::string kw = readLine("  Title keyword : ");
        lib.searchByTitle(kw);
    } else if (choice == 2) {
        std::string kw = readLine("  Author name   : ");
        lib.searchByAuthor(kw);
    } else {
        std::cout << "  [!] Invalid choice.\n";
    }
    Utils::pauseScreen();
}

// ── Main Menu ──────────────────────────────────────────────────────────────

int main() {
    system("mkdir -p data");
    Library lib("data/books.dat", "data/members.dat");

    while (true) {
        Utils::printHeader("LIBRARY MANAGEMENT SYSTEM");
        std::cout << "  -- Books --\n"
                  << "  [1]  Add Book\n"
                  << "  [2]  Remove Book\n"
                  << "  [3]  View All Books\n"
                  << "  [4]  View Book Details\n\n"
                  << "  -- Members --\n"
                  << "  [5]  Add Member\n"
                  << "  [6]  Remove Member\n"
                  << "  [7]  View All Members\n"
                  << "  [8]  View Member Details\n\n"
                  << "  -- Transactions --\n"
                  << "  [9]  Issue Book\n"
                  << "  [10] Return Book\n"
                  << "  [11] View Borrowed Books\n\n"
                  << "  -- Search --\n"
                  << "  [12] Search Books\n\n"
                  << "  [0]  Exit\n\n";

        int choice = readInt("  Enter choice : ");

        switch (choice) {
            case 1:  addBookMenu(lib);      break;
            case 2:  removeBookMenu(lib);   break;
            case 3:  viewBooksMenu(lib);    break;
            case 4:  viewBookMenu(lib);     break;
            case 5:  addMemberMenu(lib);    break;
            case 6:  removeMemberMenu(lib); break;
            case 7:  viewMembersMenu(lib);  break;
            case 8:  viewMemberMenu(lib);   break;
            case 9:  issueBookMenu(lib);    break;
            case 10: returnBookMenu(lib);   break;
            case 11: viewBorrowedMenu(lib); break;
            case 12: searchMenu(lib);       break;
            case 0:
                Utils::printHeader("GOODBYE");
                std::cout << "  Thank you for using the Library Management System.\n\n";
                return 0;
            default:
                std::cout << "  [!] Invalid choice.\n";
                Utils::pauseScreen();
        }
    }
}
