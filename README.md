# 📚 Library Management System (C++)

A console-based Library Management System built in C++ using **Object-Oriented Programming** and **File Handling** for persistent storage.

---

## Features

| Feature | Description |
|---|---|
| Add / Remove Book | Manage library book inventory |
| Add / Remove Member | Register and remove library members |
| Issue Book | Assign a book copy to a member |
| Return Book | Process book returns |
| Search by Title | Case-insensitive keyword search |
| Search by Author | Case-insensitive author search |
| View Borrowed Books | List all books held by a member |
| Persistent Storage | Data saved to `data/books.dat` and `data/members.dat` |

---

## Project Structure

```
library-management/
├── include/
│   ├── Book.h          # Book class declaration
│   ├── Member.h        # Member class declaration
│   ├── Library.h       # Library class declaration
│   └── Utils.h         # Utility helpers
├── src/
│   ├── Book.cpp        # Book operations & serialization
│   ├── Member.cpp      # Member operations & serialization
│   ├── Library.cpp     # Core library logic & file I/O
│   ├── Utils.cpp       # UI helpers
│   └── main.cpp        # Menu-driven entry point
├── data/               # Auto-created; stores books.dat & members.dat
├── Makefile
└── README.md
```

---

## OOP Concepts Used

- **Encapsulation** — Private data members with public accessors
- **Abstraction** — `Library` hides file I/O behind clean methods
- **Separation of Concerns** — `Book`, `Member`, `Library`, `Utils` each have single responsibilities
- **Constructor Overloading** — Default and parameterized constructors

---

## Build & Run

```bash
make
./library_app

# or shortcut:
make run
```

### Clean build files
```bash
make clean
```

---

## Data Storage Format

**books.dat**
```
1001|The Great Gatsby|F. Scott Fitzgerald|978-0743273565|3|2
1002|Clean Code|Robert C. Martin|978-0132350884|2|2
```

**members.dat**
```
2001|Alice Smith|9876543210|1001,1002
2002|Bob Jones|9123456789|
```

---

## License

MIT License — free to use and modify for educational purposes.
