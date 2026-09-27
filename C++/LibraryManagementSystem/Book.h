#pragma once
#include "LibraryItem.h"

// Book class inherits from LibraryItem
class Book : public LibraryItem {
private:
    int pages;
    string genre;
public:
    Book(int id, string title, string creator, int year, bool available, int pages, string genre,
        string borrowerName = "", string borrowDate = "");
    string getType() const override;
    void display() const override;
    void printToStream(ostream& out) const override;
    void saveToFile(ofstream& out) const override;
    double calculateLateFee(int overdueDays) const override;
};
