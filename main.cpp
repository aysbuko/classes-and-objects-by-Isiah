#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Book {
    private:
        string title;
        string author;
        int releaseDate;
        string genre;

    public:
        Book(string title, string author, int releaseDate, string genre) {
            this->title = title;
            this->author = author;
            this->releaseDate = releaseDate;
            this->genre = genre;
        }

        ~Book() {
            cout << "Book \"" << title << "\" has been removed from the system." << endl;
        }

        string getTitle() const {
            return title;
        }

        void display() const {
            cout << "---------------Book Details---------------" << endl;
            cout << "Title: " << title << endl;
            cout << "Author: " << author << endl;
            cout << "Release Date: " << releaseDate << endl;
            cout << "Genre: " << genre << endl;
        }
};

class Library {
    private:
        vector<Book> books;

    public:
        Library() {
            books.emplace_back("Noli Me Tangere", "Jose Rizal", 1887, "Novel");
            books.emplace_back("El Filibusterismo", "Jose Rizal", 1891, "Novel");
        }

        void addBook() {
            string title, author, genre;
            int year;

            cin.ignore();
            cout << "Enter book title: ";
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);
            cout << "Enter release year: ";
            cin >> year;
            cin.ignore();
            cout << "Enter genre: ";
            getline(cin, genre);

            books.emplace_back(title, author, year, genre);
            cout << "Book added successfully!" << endl;
        }

        void displayBooks() const {
            if (books.empty()) {
                cout << "No books in the library." << endl;
                return;
            }

            cout << "---------------Library Books---------------" << endl;
            for (const auto& book : books) {
                book.display();
            }
        }

        void searchBook() const {
            if (books.empty()) {
                cout << "No books available to search." << endl;
                return;
            }

            cin.ignore();
            string searchTitle;
            cout << "Enter book title to search: ";
            getline(cin, searchTitle);

            for (const auto& book : books) {
                if (book.getTitle() == searchTitle) {
                    cout << "Book found!" << endl;
                    book.display();
                    return;
                }
            }

            cout << "Book not found." << endl;
        }
};

int main() {
    Library library;
    int choice;

    while (true) {
        cout << "\n---------------Library Menu---------------" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Display All Books" << endl;
        cout << "3. Search Book by Title" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            library.addBook();
        }
        else if (choice == 2) {
            library.displayBooks();
        }
        else if (choice == 3) {
            library.searchBook();
        }
        else if (choice == 4) {
            cout << "Exiting the library system. Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid choice. Try again!" << endl;
        }
    }

    return 0;
}
