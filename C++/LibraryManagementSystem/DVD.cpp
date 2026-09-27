#include "DVD.h"

DVD::DVD(int id, string title, string creator, int year, bool available, double duration, string ageRating,
    string borrowerName, string borrowDate)
    : LibraryItem(id, title, creator, year, available, borrowerName, borrowDate), duration(duration), ageRating(ageRating) {
}

string DVD::getType() const { return "DVD"; }

void DVD::display() const {
    cout << "Type: DVD" << endl;
    cout << "ID: " << getID() << endl;
    cout << "Title: " << getTitle() << endl;
    cout << "Creator: " << getCreator() << endl;
    cout << "Year: " << getYear() << endl;
    cout << "Duration: " << duration << endl;
    cout << "Age Rating: " << ageRating << endl;
    cout << "Status: " << (isAvailable() ? "Available" : "Borrowed") << endl;
    if (!isAvailable()) {
        cout << "Borrower: " << getBorrowerName() << endl;
        cout << "Borrow Date: " << getBorrowDate() << endl;
    }
}

void DVD::printToStream(ostream& out) const {
    out << "Type: DVD" << endl;
    out << "ID: " << getID() << endl;
    out << "Title: " << getTitle() << endl;
    out << "Creator: " << getCreator() << endl;
    out << "Year: " << getYear() << endl;
    out << "Duration: " << duration << endl;
    out << "Age Rating: " << ageRating << endl;
    out << "Status: " << (isAvailable() ? "Available" : "Borrowed") << endl;
    if (!isAvailable()) {
        out << "Borrower: " << getBorrowerName() << endl;
        out << "Borrow Date: " << getBorrowDate() << endl;
    }
}

void DVD::saveToFile(ofstream& out) const {
    out << "DVD|"
        << getID() << "|"
        << getTitle() << "|"
        << getCreator() << "|"
        << getYear() << "|"
        << isAvailable() << "|"
        << getBorrowerName() << "|"
        << getBorrowDate() << "|"
        << duration << "|"
        << ageRating << endl;
}

double DVD::calculateLateFee(int overdueDays) const {
    return 1.00 * overdueDays;
}
