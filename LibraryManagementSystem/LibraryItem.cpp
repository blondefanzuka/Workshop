#include "LibraryItem.h"

LibraryItem::LibraryItem() : id(0), title(""), creator(""), publicationYear(0), available(true),
    borrowerName(""), borrowDate("") {
}

LibraryItem::LibraryItem(int id, string title, string creator, int publicationYear, bool available,
    string borrowerName, string borrowDate)
    : id(id), title(title), creator(creator), publicationYear(publicationYear),
    available(available), borrowerName(borrowerName), borrowDate(borrowDate) {
}

LibraryItem::~LibraryItem() {
}

int LibraryItem::getID() const { return id; }
string LibraryItem::getTitle() const { return title; }
string LibraryItem::getCreator() const { return creator; }
int LibraryItem::getYear() const { return publicationYear; }
bool LibraryItem::isAvailable() const { return available; }
string LibraryItem::getBorrowerName() const { return borrowerName; }
string LibraryItem::getBorrowDate() const { return borrowDate; }

void LibraryItem::setAvailable(bool a) { available = a; }
void LibraryItem::setBorrowerName(string name) { borrowerName = name; }
void LibraryItem::setBorrowDate(string date) { borrowDate = date; }

// Compares two items by publication year
bool operator<(const LibraryItem& a, const LibraryItem& b) {
    return a.getYear() < b.getYear();
}

// Compares two items by ID
bool operator==(const LibraryItem& a, const LibraryItem& b) {
    return a.getID() == b.getID();
}

// Allows writing an item to cout or a file using <<
ostream& operator<<(ostream& out, const LibraryItem& item) {
    item.printToStream(out);
    return out;
}
