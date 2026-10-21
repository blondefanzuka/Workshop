#include "Book.h"

Book::Book(int id, string title, string creator, int year, bool available, int pages, string genre,
    string borrowerName, string borrowDate)
    : LibraryItem(id, title, creator, year, available, borrowerName, borrowDate), pages(pages), genre(genre) {
}

string Book::getType() const { return "Book"; }

void Book::display() const {
    cout << "Type: Book" << endl;
    cout << "ID: " << getID() << endl;
    cout << "Title: " << getTitle() << endl;
    cout << "Creator: " << getCreator() << endl;
    cout << "Year: " << getYear() << endl;
    cout << "Pages: " << pages << endl;
    cout << "Genre: " << genre << endl;
    cout << "Status: " << (isAvailable() ? "Available" : "Borrowed") << endl;
    if (!isAvailable()) {
        cout << "Borrower: " << getBorrowerName() << endl;
        cout << "Borrow Date: " << getBorrowDate() << endl;
    }
}

void Book::printToStream(ostream& out) const {
    out << "Type: Book" << endl;
    out << "ID: " << getID() << endl;
    out << "Title: " << getTitle() << endl;
    out << "Creator: " << getCreator() << endl;
    out << "Year: " << getYear() << endl;
    out << "Pages: " << pages << endl;
    out << "Genre: " << genre << endl;
    out << "Status: " << (isAvailable() ? "Available" : "Borrowed") << endl;
    if (!isAvailable()) {
        out << "Borrower: " << getBorrowerName() << endl;
        out << "Borrow Date: " << getBorrowDate() << endl;
    }
}

void Book::saveToFile(ofstream& out) const {
    out << "Book|"
        << getID() << "|"
        << getTitle() << "|"
        << getCreator() << "|"
        << getYear() << "|"
        << isAvailable() << "|"
        << getBorrowerName() << "|"
        << getBorrowDate() << "|"
        << pages << "|"
        << genre << endl;
}

double Book::calculateLateFee(int overdueDays) const {
    return 0.50 * overdueDays;
}
