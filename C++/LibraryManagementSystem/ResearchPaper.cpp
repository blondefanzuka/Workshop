#include "ResearchPaper.h"

ResearchPaper::ResearchPaper(int id, string title, string creator, int year, bool available, string conference, string doi,
    string borrowerName, string borrowDate)
    : LibraryItem(id, title, creator, year, available, borrowerName, borrowDate), conference(conference), doi(doi) {
}

string ResearchPaper::getType() const { return "ResearchPaper"; }

void ResearchPaper::display() const {
    cout << "Type: ResearchPaper" << endl;
    cout << "ID: " << getID() << endl;
    cout << "Title: " << getTitle() << endl;
    cout << "Creator: " << getCreator() << endl;
    cout << "Year: " << getYear() << endl;
    cout << "Conference: " << conference << endl;
    cout << "DOI: " << doi << endl;
    cout << "Status: " << (isAvailable() ? "Available" : "Borrowed") << endl;
    if (!isAvailable()) {
        cout << "Borrower: " << getBorrowerName() << endl;
        cout << "Borrow Date: " << getBorrowDate() << endl;
    }
}

void ResearchPaper::printToStream(ostream& out) const {
    out << "Type: ResearchPaper" << endl;
    out << "ID: " << getID() << endl;
    out << "Title: " << getTitle() << endl;
    out << "Creator: " << getCreator() << endl;
    out << "Year: " << getYear() << endl;
    out << "Conference: " << conference << endl;
    out << "DOI: " << doi << endl;
    out << "Status: " << (isAvailable() ? "Available" : "Borrowed") << endl;
    if (!isAvailable()) {
        out << "Borrower: " << getBorrowerName() << endl;
        out << "Borrow Date: " << getBorrowDate() << endl;
    }
}

void ResearchPaper::saveToFile(ofstream& out) const {
    out << "ResearchPaper|"
        << getID() << "|"
        << getTitle() << "|"
        << getCreator() << "|"
        << getYear() << "|"
        << isAvailable() << "|"
        << getBorrowerName() << "|"
        << getBorrowDate() << "|"
        << conference << "|"
        << doi << endl;
}

double ResearchPaper::calculateLateFee(int overdueDays) const {
    return 0.20 * overdueDays;
}
