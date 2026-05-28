#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Book {
private:
    int bookID;
    char title[50];
    char author[50];
    bool issued;

public:
    void addBook() {
        cout << "\nEnter Book ID: ";
        cin >> bookID;

        cin.ignore();

        cout << "Enter Book Title: ";
        cin.getline(title, 50);

        cout << "Enter Author Name: ";
        cin.getline(author, 50);

        issued = false;
    }

    void displayBook() {
        cout << "\n--------------------------------";
        cout << "\nBook ID      : " << bookID;
        cout << "\nTitle        : " << title;
        cout << "\nAuthor       : " << author;
        cout << "\nStatus       : ";

        if (issued)
            cout << "Issued";
        else
            cout << "Available";

        cout << "\n--------------------------------\n";
    }

    int getBookID() {
        return bookID;
    }

    char* getTitle() {
        return title;
    }

    char* getAuthor() {
        return author;
    }

    bool isIssued() {
        return issued;
    }

    void issueBook() {
        issued = true;
    }

    void returnBook() {
        issued = false;
    }
};

void addNewBook() {
    Book b;

    ofstream file("library.dat", ios::binary | ios::app);

    b.addBook();

    file.write((char*)&b, sizeof(b));

    file.close();

    cout << "\nBook Added Successfully!\n";
}

void displayAllBooks() {
    Book b;

    ifstream file("library.dat", ios::binary);

    if (!file) {
        cout << "\nNo Records Found!\n";
        return;
    }

    while (file.read((char*)&b, sizeof(b))) {
        b.displayBook();
    }

    file.close();
}

void searchByTitle() {
    Book b;
    char title[50];
    bool found = false;

    ifstream file("library.dat", ios::binary);

    cin.ignore();

    cout << "\nEnter Title to Search: ";
    cin.getline(title, 50);

    while (file.read((char*)&b, sizeof(b))) {

        if (strcmp(b.getTitle(), title) == 0) {
            b.displayBook();
            found = true;
        }
    }

    file.close();

    if (!found) {
        cout << "\nBook Not Found!\n";
    }
}

void searchByAuthor() {
    Book b;
    char author[50];
    bool found = false;

    ifstream file("library.dat", ios::binary);

    cin.ignore();

    cout << "\nEnter Author Name: ";
    cin.getline(author, 50);

    while (file.read((char*)&b, sizeof(b))) {

        if (strcmp(b.getAuthor(), author) == 0) {
            b.displayBook();
            found = true;
        }
    }

    file.close();

    if (!found) {
        cout << "\nBook Not Found!\n";
    }
}

void issueBook() {
    Book b;
    int id;
    bool found = false;

    fstream file("library.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Book ID to Issue: ";
    cin >> id;

    while (file.read((char*)&b, sizeof(b))) {

        if (b.getBookID() == id) {

            if (b.isIssued()) {
                cout << "\nBook Already Issued!\n";
            }
            else {
                b.issueBook();

                int pos = (-1) * sizeof(b);

                file.seekp(pos, ios::cur);

                file.write((char*)&b, sizeof(b));

                cout << "\nBook Issued Successfully!\n";
            }

            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "\nBook Not Found!\n";
    }
}

void returnBook() {
    Book b;
    int id;
    bool found = false;

    fstream file("library.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Book ID to Return: ";
    cin >> id;

    while (file.read((char*)&b, sizeof(b))) {

        if (b.getBookID() == id) {

            if (!b.isIssued()) {
                cout << "\nBook Already Available!\n";
            }
            else {
                b.returnBook();

                int pos = (-1) * sizeof(b);

                file.seekp(pos, ios::cur);

                file.write((char*)&b, sizeof(b));

                cout << "\nBook Returned Successfully!\n";
            }

            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "\nBook Not Found!\n";
    }
}

int main() {

    int choice;

    do {

        cout << "\n========== LIBRARY MANAGEMENT SYSTEM ==========\n";

        cout << "\n1. Add Book";
        cout << "\n2. Display All Books";
        cout << "\n3. Search Book by Title";
        cout << "\n4. Search Book by Author";
        cout << "\n5. Issue Book";
        cout << "\n6. Return Book";
        cout << "\n7. Exit";

        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            addNewBook();
            break;

        case 2:
            displayAllBooks();
            break;

        case 3:
            searchByTitle();
            break;

        case 4:
            searchByAuthor();
            break;

        case 5:
            issueBook();
            break;

        case 6:
            returnBook();
            break;

        case 7:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 7);

    return 0;
}
