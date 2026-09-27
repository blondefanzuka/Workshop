#pragma once
#include "LibraryItem.h"

// DVD class inherits from LibraryItem
class DVD : public LibraryItem {
private:
    double duration;
    string ageRating;
public:
    DVD(int id, string title, string creator, int year, bool available, double duration, string ageRating,
        string borrowerName = "", string borrowDate = "");
    string getType() const override;
    void display() const override;
    void printToStream(ostream& out) const override;
    void saveToFile(ofstream& out) const override;
    double calculateLateFee(int overdueDays) const override;
};
