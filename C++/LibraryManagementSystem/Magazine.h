#pragma once
#include "LibraryItem.h"

// Magazine class inherits from LibraryItem
class Magazine : public LibraryItem {
private:
    int issueNumber;
    string month;
public:
    Magazine(int id, string title, string creator, int year, bool available, int issueNumber, string month,
        string borrowerName = "", string borrowDate = "");
    string getType() const override;
    void display() const override;
    void printToStream(ostream& out) const override;
    void saveToFile(ofstream& out) const override;
    double calculateLateFee(int overdueDays) const override;
};
