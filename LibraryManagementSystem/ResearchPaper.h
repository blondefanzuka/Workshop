#pragma once
#include "LibraryItem.h"

// ResearchPaper class inherits from LibraryItem
class ResearchPaper : public LibraryItem {
private:
    string conference;
    string doi;
public:
    ResearchPaper(int id, string title, string creator, int year, bool available, string conference, string doi,
        string borrowerName = "", string borrowDate = "");
    string getType() const override;
    void display() const override;
    void printToStream(ostream& out) const override;
    void saveToFile(ofstream& out) const override;
    double calculateLateFee(int overdueDays) const override;
};
