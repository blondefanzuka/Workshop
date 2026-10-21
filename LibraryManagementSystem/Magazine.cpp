#include "Magazine.h"

Magazine::Magazine(int id, string title, string creator, int year, bool available, int issueNumber, string month,
    string borrowerName, string borrowDate)
    : LibraryItem(id, title, creator, year, available, borrowerName, borrowDate), issueNumber(issueNumber), month(month) {
}

string Magazine::getType() const { return "Magazine"; }

void Magazine::display() const {
    cout << "Type: Magazine" << endl;
    cout << "ID: " << getID() << endl;
    cout << "Title: " << getTitle() << endl;
    cout << "Creator: " << getCreator() << endl;
    cout << "Year: " << getYear() << endl;
    cout << "Issue Number: " << issueNumber << endl;
    cout << "Month: " << month << endl;
    cout << "Status: " << (isAvailable() ? "Available" : "Borrowed") << endl;
    if (!isAvailable()) {
        cout << "Borrower: " << getBorrowerName() << endl;
        cout << "Borrow Date: " << getBorrowDate() << endl;
    }
}

void Magazine::printToStream(ostream& out) const {
    out << "Type: Magazine" << endl;
    out << "ID: " << getID() << endl;
    out << "Title: " << getTitle() << endl;
    out << "Creator: " << getCreator() << endl;
    out << "Year: " << getYear() << endl;
    out << "Issue Number: " << issueNumber << endl;
    out << "Month: " << month << endl;
    out << "Status: " << (isAvailable() ? "Available" : "Borrowed") << endl;
    if (!isAvailable()) {
        out << "Borrower: " << getBorrowerName() << endl;
        out << "Borrow Date: " << getBorrowDate() << endl;
    }
}

void Magazine::saveToFile(ofstream& out) const {
    out << "Magazine|"
        << getID() << "|"
        << getTitle() << "|"
        << getCreator() << "|"
        << getYear() << "|"
        << isAvailable() << "|"
        << getBorrowerName() << "|"
        << getBorrowDate() << "|"
        << issueNumber << "|"
        << month << endl;
}

double Magazine::calculateLateFee(int overdueDays) const {
    return 0.30 * overdueDays;
}
